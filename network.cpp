#include "network.h"

Network::Network(vector<Neuron*> all_neurons) :
  global_clock_(0), all_neurons_(all_neurons)
{
  //! When creating the network, the neurons are not connected yet
  nb_neurons_ = all_neurons_.size();
  for (size_t i(0); i < nb_neurons_; ++i) {
    vector<int> subVector;
    connexions_.push_back(subVector);
    for (size_t j(0); j < nb_neurons_; ++j) {
      connexions_[i].push_back(0);
    }
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

  //! Initialize all connexions to 0
  nb_neurons_ = all_neurons_.size();
  for (size_t i(0); i < nb_neurons_; ++i) {
    vector<int> subVector;
    connexions_.push_back(subVector);
    for (size_t j(0); j < nb_neurons_; ++j) {
      connexions_[i].push_back(0);
    }
  }

    // For each neuron, we ramdomly choose 1000 excitatory neurons and 250
    // inhibitory neurons that will target this particular neuron
    random_device rd;
    mt19937 gen(rd());
    // Excitatory neurons are from 0 to 9999 in the vector
    int indexFirstExcitatoryNeuron(0);
    int indexLastExcitatoryNeuron(9999);
    // Inhibitory neurons are from 10000 to 12499 in the vector
    int indexFirstInhibitoryNeuron(10000);
    int indexLastInhibitoryNeuron(12499);
    uniform_int_distribution<> distribEx(indexFirstExcitatoryNeuron, indexLastExcitatoryNeuron);
    uniform_int_distribution<> distribIn(indexFirstInhibitoryNeuron, indexLastInhibitoryNeuron);

  // We initialize all the connexions of the neurons in the network
  for (size_t i(0); i < nb_neurons_; ++i) {

    // This neuron will be "target" by C_EXCI connexions from excitatory neurons
    for (size_t i(0); i < C_EXCI; ++i) {
      int r(distribEx(gen));
      addConnexion(r, i);
      // Neuron in position i of the vector all_neurons_ have a synaptic connexion
      // to neuron in position r : r -> i (i is a post-synaptic neuron of neuron r)
    }

    // This neuron will be "target" by C_INHI connexions from excitatory neurons
    for (size_t i(0); i < C_INHI; ++i) {
      int r(distribIn(gen));
      addConnexion(r, i);
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

/******************************************************************************/

void Network::addNeuron(Neuron* n) {
  assert(n != nullptr);
  all_neurons_.push_back(n);
}

void Network::addConnexion(unsigned int id_n1, unsigned int id_n2) {
    assert(id_n1 < nb_neurons_);
    assert(id_n2 < nb_neurons_);
    connexions_[id_n1][id_n2] += 1;
    // Neuron2 (n2) is a post-synaptic neuron of neuron1 (n1) (for 1 connexion)
    // It is possible to have multiple connexions between the same neurons
}

void Network::deleteConnexion(unsigned int id_n1, unsigned int id_n2) {
    assert(id_n1 < nb_neurons_);
    assert(id_n2 < nb_neurons_);
    connexions_[id_n1][id_n2] -= 1;
}


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
     */
    bool zero(true); //If the external current is 0, then this boolean is true
    if ((global_clock_ >= inf) and (global_clock_ <= sup)) {
      zero = false;
    } else {
      zero = true;
    }

    for (size_t i(0); i < all_neurons_.size(); ++i) {
      assert(all_neurons_[i] != nullptr);

      /*all_neurons_[i]->setIExt(0); // à enlever là c'est juste pour que l'input current du neuron2 soit = 0
      if (i == 0) { // à enlever c'est juste pour que input current neuron2=0 et pas neuron1
        // We update the input current for the neuron 1*/
        if (zero) {
          all_neurons_[i]->setIExt(0);
        } else {
          all_neurons_[i]->setIExt(EXT_CURRENT);
        }
        // Since EXT_CURRENT = 0.O (Constants.hpp) it will always be zero
      //}

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

     vector<size_t> post;
     vector<int> nb_connexions_with_each_postsyn;
     /*
      * We look for the post-syn neurons and store their index.
      * We store the number of connexions between this neuron and each of his
      * post-synaptic neurons since this number can be different (from 0 or 1).
      */
     for (size_t i(0); i < nb_neurons_; ++i) {
       if (connexions_[id_n][i] > 0) {
         post.push_back(i);
         nb_connexions_with_each_postsyn.push_back(connexions_[id_n][i]);
       }
     }

     size_t nb_post(post.size()); // Number of post-synaptic neurons
     for (size_t i(0); i < nb_post; ++i) {
       assert(all_neurons_[post[i]] != nullptr);
       double j; // spike response amplitude
       j = (all_neurons_[id_n]->getJ())*(nb_connexions_with_each_postsyn[i]);
       /*
        * = spike response amplitude of the neuron
        * (which is different between excitatory and inhibitory neurons)
        * multiplied by the number of connexions between these 2 neurons.
        */
       all_neurons_[post[i]]->receive(D, j);
     }

   }
 }
