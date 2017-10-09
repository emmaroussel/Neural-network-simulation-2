#include "neuron2.h"


//CONSTRUCTOR
Neuron::Neuron() : membrane_potential_(V_INI), i_ext_(0), nb_spikes_(0),
                   spike_time_(0), refractory_(false), clock_(T_START/H),
                   refractory_steps_(REFRAC_TIME/H), post_syn_(nullptr)
{}

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

bool Neuron::isRefractory() const {
  return refractory_;
}

Neuron* Neuron::getPostSyn() {
      return post_syn_;
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

void Neuron::setRefractory(bool state) {
  refractory_ = state;
}

void Neuron::setPostSyn(Neuron* n) {
  post_syn_ = n;
}

/**********************************************************************************/

//METHODS
void Neuron::updateMembranePotential(double current, double h, double tau, double resistance) {
    setMembranePotential(exp(-h/tau)*membrane_potential_ + current*resistance*(1-exp(-h/tau)));
}

bool Neuron::update(long steps) {

 double t_stop(clock_ + steps);
 double refrac_step(REFRAC_TIME/H); //we express the refactory time in terms of steps
 bool spike(false);

 while (clock_ < t_stop) {

   if (membrane_potential_ > V_THRS) {
     spike_time_ = clock_;
     ++nb_spikes_;
     spike = true;
     setRefractory(true);
   }

   if (refractory_) {
     membrane_potential_ = V_REFRAC;
     ++refractory_steps_;

     if (refractory_steps_ > refrac_step) {
       setRefractory(false);
       membrane_potential_ = V_RESET;
       refractory_steps_ = 0;
     }
     
   } else {
        updateMembranePotential(i_ext_, H, TAU, RESISTANCE);
   }

   updateAllMembranePotentials(membrane_potential_);

   ++clock_;

  }

 return spike;
}


void Neuron::receive(double j) {
  membrane_potential_ += j;
}
