#include "network.h"

Network::Network(vector<Neuron*> all_neurons) :
  global_clock_(0), all_neurons_(all_neurons), nb_neurons_(all_neurons.size())
{
  // When creating the network, the neurons are not connected yet
for (size_t i(0); i < nb_neurons_; ++i) {
  vector<size_t> subVector;
  targets_.push_back(subVector);
}

}


Network::Network() : global_clock_(0)
{
  // We create N_EXCI excitatory neurons
  for (size_t i(0); i < N_EXCI; ++i) {
    all_neurons_.push_back(new Neuron(true));
  }

  // We create N_INHI inhibitory neurons
  for (size_t i(0); i < N_INHI; ++i) {
    all_neurons_.push_back(new Neuron(false));
  }

  // Initialize all connexions to 0
  nb_neurons_ = all_neurons_.size();

  for (size_t i(0); i < nb_neurons_; ++i) {
    vector<size_t> subVector;
    targets_.push_back(subVector);
  }

    /*
     * For each neuron, we ramdomly choose 1000 excitatory neurons and 250
     * inhibitory neurons that will target this particular neuron
     */
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distribEx(indexFirstExcitatoryNeuron, indexLastExcitatoryNeuron);
    uniform_int_distribution<> distribIn(indexFirstInhibitoryNeuron, indexLastInhibitoryNeuron);
    //these indices are found in the Constants.hpp file

  // We initialize all the connexions of the neurons in the network
  for (size_t i(0); i < nb_neurons_; ++i) {

    // This neuron will be "target" by C_EXCI connexions from excitatory neurons
    for (size_t j(0); j < C_EXCI; ++j) {
      int random_index(distribEx(gen));
      addConnexion(random_index, i);

      /*
       * Neuron in position i of the vector all_neurons_ have a synaptic connexion
       * to neuron in position random_index :
       * random_index neuron -> i neuron
       * (i is a post-synaptic neuron of neuron random_index)
       */
    }

    // This neuron will be "target" by C_INHI connexions from inhibitory neurons
    for (size_t k(0); k < C_INHI; ++k) {
      int random_index(distribIn(gen));
      addConnexion(random_index, i);
    }
  }

}


Network::~Network()
{
    for (auto& neuron : all_neurons_) {
        delete neuron;
    }
    all_neurons_.clear();
}

/******************************************************************************/

vector<Neuron*> Network::getAllNeurons() const {
  return all_neurons_;
}

vector< vector<size_t> > Network::getTargets() const {
  return targets_;
}

vector<size_t>  Network::getNeuronsIndexes() const {
  return neurons_idx_;
}

vector<double> Network::getSpikeTimes() const {
  return spike_times_;
}

/******************************************************************************/

void Network::addNeuron(Neuron* n) {
  assert(n != nullptr);
  all_neurons_.push_back(n);
}

void Network::addConnexion(unsigned int id_n1, unsigned int id_n2) {
    assert(id_n1 < nb_neurons_);
    assert(id_n2 < nb_neurons_);

    targets_[id_n1].push_back(id_n2);
  //  weight[id_n1].push_back(weight);
  //  connexions_[id_n1][id_n2] += 1;
    /*
     * Neuron2 (n2) is a post-synaptic neuron of neuron1 (n1) (for 1 connexion)
     * It is possible to have multiple connexions between the same neurons.
     */
}

/*void Network::deleteConnexion(unsigned int id_n1, unsigned int id_n2) {
    assert(id_n1 < nb_neurons_);
    assert(id_n2 < nb_neurons_);
    connexions_[id_n1][id_n2] -= 1;
}*/


void Network::updateNetwork() {

  long t_stop(T_STOP/H); //in terms of integration steps
  double inf(0); // in ms
  double sup(100); // in ms
  assert(inf < sup);

  // We transform these times in terms of steps
  assert(H != 0);
  inf /= H;
  sup /= H;

  while (global_clock_ < t_stop) {
    /*
     * Update the input current, if we assume the input current is the same
     * for all neurons.
     * inf and sup are useful is we want to have a non-zero external current
     * during a precise period of time during the simulation.
     */
    bool zero(true); // If the external current is 0, then this boolean is true
    if ((global_clock_ >= inf) and (global_clock_ <= sup)) {
      zero = false;
    } else {
      zero = true;
    }

    for (size_t i(0); i < all_neurons_.size(); ++i) {
      assert(all_neurons_[i] != nullptr);

        if (zero) {
          all_neurons_[i]->setIExt(0);
        } else {
          all_neurons_[i]->setIExt(EXT_CURRENT);
        }
        // Since EXT_CURRENT = 0.0 (Constants.hpp) it will always be zero

      updateOneNeuron(i);
    }

    ++global_clock_;

  }

}


 void Network::updateOneNeuron(unsigned int id_n) {
   bool spike(false);
   spike = all_neurons_[id_n]->update(1);

   /*
    * If the neuron spikes, then we udpate the membrane potential of
    * its post-synaptic neurons.
    */
   if (spike) {
      /*
       * We look for the post-syn neurons of neuron of index id_n.
       * The neuron id_N has a number of connexions greater than zero with each
       * of its post-synaptic neurons. (We look in the connexion matrix, only
       * in the id_n row)
       * These neurons receive an amplitude response from neuron id_n which
       * is proportionnal to the number of connexions between neuron id_n
       * and the post-synaptic neuron concerned.
       */
     double j_id_n(all_neurons_[id_n]->getJ()); // weight of a connexion from the id_n neuron
     size_t nb_targets(targets_[id_n].size());
     for (size_t i(0); i < nb_targets; ++i) {
       assert(all_neurons_[targets_[id_n][i]] != nullptr);

       all_neurons_[targets_[id_n][i]]->receive(D, j_id_n);
     }


     /*
      * Neuron has spiked : we add this time spike (corresponding to the global_clock_)
      * to spike_times_ ;
      * we add the index of the neuron (id_n) to neurons_idx_
      */
      spike_times_.push_back(global_clock_);
      neurons_idx_.push_back(id_n);

   }
 }
