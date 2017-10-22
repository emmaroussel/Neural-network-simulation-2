#include "neuron2.h"

Neuron::Neuron() : membrane_potential_(V_INI), i_ext_(0), nb_spikes_(0),
                   spike_time_(0), refractory_(false), clock_(T_START/H),
                   refractory_steps_(0), rb_index_(0)
{
  for (size_t i(0); i < ring_buffer_.size(); ++i) {
    ring_buffer_[i] = 0;
  }

}

Neuron::Neuron(double potential) :
  membrane_potential_(potential), i_ext_(0), nb_spikes_(0),
  spike_time_(0), refractory_(false), clock_(T_START/H),
  refractory_steps_(0), rb_index_(0)
{
  for (size_t i(0); i < ring_buffer_.size(); ++i) {
    ring_buffer_[i] = 0;
  }

}


Neuron::~Neuron()
{}

/**********************************************************************************/

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

/**********************************************************************************/

void Neuron::setMembranePotential(double potential) {
  membrane_potential_ = potential;
}

void Neuron::setIExt(double current) {
  i_ext_ = current;
}

void Neuron::updateAllMembranePotentials(double potential) {
    allMembranePotentials_.push_back(potential);
}

/**********************************************************************************/

void Neuron::updateMembranePotential() {
    setMembranePotential(
      exp(-H/TAU)*membrane_potential_
      + i_ext_*RESISTANCE*(1-exp(-H/TAU))
      + ring_buffer_[rb_index_]
    );
    ring_buffer_[rb_index_] = 0;
}

bool Neuron::update(long steps) {
 if (steps == 0) return false;

 double t_stop(clock_ + steps);
 bool spike(false);

 while (clock_ < t_stop) {

   if (membrane_potential_ >= V_THRS) {
     spike_time_ = clock_;
     ++nb_spikes_;
     spike = true;
     refractory_ = true;
   }

   updateAllMembranePotentials(membrane_potential_);

   if (refractory_) {

     membrane_potential_ = V_REFRAC;
     ++refractory_steps_;

     if (refractory_steps_ >= REFRAC_STEPS) {
       refractory_ = false;
       membrane_potential_ = V_RESET;
       refractory_steps_ = 0;
     }

   } else {
     updateMembranePotential();
   }

   updateRingBuffer();
   ++clock_;

  }

 return spike;
}


void Neuron::receive(int delay, double j) {
  assert(delay >= 0);
  size_t position((rb_index_ + delay) % (D+1));
  ring_buffer_[position] += j;
}

void Neuron::updateRingBuffer() {
  /*
   * If the read-out index of the ring buffer is at "the end" of the
   * ring buffer, then we move the read-out index to the first position.
   */
  if (rb_index_ == ring_buffer_.size() - 1) {
    rb_index_ = 0;
  } else {
    ++rb_index_;
  }
}
