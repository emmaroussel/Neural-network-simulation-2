#include "neuron2.h"


//CONSTRUCTOR
Neuron::Neuron() : membrane_potential_(V_INI), i_ext_(0), nb_spikes_(0),
                   spike_time_(0), refractory_(false), clock_(T_START/H),
                   refractory_steps_(REFRAC_TIME/H)
{
  for (size_t i(0); i < ring_buffer_.size(); ++i) {
    ring_buffer_[i] = 0;
  }

}

/**********************************************************************************/

//GETTERS
double Neuron::getMembranePotential() const {
  return membrane_potential_;
}

long Neuron::getNbSpikes() const {
  return nb_spikes_;
}

long Neuron::getSpikeTime() const {
  return spike_time_;
}

vector<double> Neuron::getAllMembranePotentials() const {
  return allMembranePotentials_;
}

vector<Neuron*> Neuron::getPostSynNeuron() const {
  return targets;
}

/**********************************************************************************/

//SETTERS
void Neuron::setMembranePotential(double potential) {
  membrane_potential_ = potential;
}

void Neuron::setIExt(double current) {
  i_ext_ = current;
}

void Neuron::updateAllMembranePotentials(double potential) {
    allMembranePotentials_.push_back(potential);
}

void Neuron::setPostSynNeuron(Neuron* n) {
  targets.push_back(n);
}

/**********************************************************************************/

//METHODS
void Neuron::updateMembranePotential(double current, double h, double tau, double resistance) {
    setMembranePotential(
      exp(-h/tau)*membrane_potential_
      + current*resistance*(1-exp(-h/tau))
      + ring_buffer_[0]
    );
}

bool Neuron::update(long steps) {
  if (steps <= 0) return false; //à changer avec assert

 double t_stop(clock_ + steps);
 bool spike(false);

 while (clock_ < t_stop) {

   if (membrane_potential_ > V_THRS) {
     spike_time_ = clock_;
     ++nb_spikes_;
     spike = true;
     refractory_ = true;
   }

   if (refractory_) {

     membrane_potential_ = V_REFRAC;
     ++refractory_steps_;

     if (refractory_steps_ > REFRAC_STEPS) {
       refractory_ = false;
       membrane_potential_ = V_RESET;
       refractory_steps_ = 0;
     }

   } else {
     updateMembranePotential(i_ext_, H, TAU, RESISTANCE);
   }

   updateAllMembranePotentials(membrane_potential_);
   updateRingBuffer();
   ++clock_;

  }

 return spike;
}


void Neuron::receive(double delay, double j) {
  ring_buffer_[delay] += j;
}

void Neuron::updateRingBuffer() {
  /*Each value goes up of one "floor" of the tab (at each step of time, since
  we call this method in the update of the neuron)
  The first value of the tab will be used when computing the membrane potential*/
  for (size_t i(0); i < ring_buffer_.size() -1; ++i) {
    ring_buffer_[i] = ring_buffer_[i+1];
  }

  ring_buffer_[ring_buffer_.size()-1] = 0;
}
