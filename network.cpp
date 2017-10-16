#include "network.h"

//CONSTRUCTOR
Network::Network(vector<Neuron*> all_neurons) :
  global_clock_(0), all_neurons_(all_neurons)
{
  //When creating the network, the neurons are not connected yet
  nb_neurons_ = all_neurons_.size();
  for (size_t i(0); i < nb_neurons_; ++i) {
    vector<bool> subVector;
    connexions_.push_back(subVector);
    for (size_t j(0); j < nb_neurons_; ++j) {
      connexions_[i].push_back(false);
    }
  }
}

//DESTRUCTOR
Network::~Network()
{}

//GETTER
vector<Neuron*> Network::getAllNeurons() const {
  return all_neurons_;
}

//METHODS
void Network::addNeuron(Neuron* n) {
  assert(n != nullptr);
  all_neurons_.push_back(n);
}

void Network::addConnexion(unsigned int id_n1, unsigned int id_n2) {
    assert(id_n1 < nb_neurons_);
    assert(id_n2 < nb_neurons_);
    connexions_[id_n1][id_n2] = true;
    //True meaning that the neuron2 (n2) is a post-synaptic neuron of neuron1 (n1)
}

void Network::deleteConnexion(unsigned int id_n1, unsigned int id_n2) {
    assert(id_n1 < nb_neurons_);
    assert(id_n2 < nb_neurons_);
    connexions_[id_n1][id_n2] = false;
}


void Network::updateNetwork() {

  long t_stop(T_STOP/H); //in terms of steps
  double inf(100); //in ms
  double sup(400); //in ms
  assert(inf > T_START);
  assert(sup < T_STOP);
  assert(inf < sup);

  //We transform these times in terms of steps
  assert(H != 0);
  inf /= H;
  sup /= H;

  while (global_clock_ < t_stop) {
    /*Update the input current, if we assume the input current is the same
    for all neurons*/
    bool zero(true); //If the external current is 0, then this boolean is true
    if ((global_clock_ >= inf) and (global_clock_ <= sup)) {
      zero = false;
    } else {
      zero = true;
    }

    for (size_t i(0); i < all_neurons_.size(); ++i) {
      assert(all_neurons_[i] != nullptr);

      all_neurons_[i]->setIExt(0); //à enlever là c'est juste pour que l'input current du neuron2 soit = 0
      if (i == 0) { //à enlever c'est juste pour que input current neuron2=0 et pas neuron1
        //We update the input current for the neuron 1
        if (zero) {
          all_neurons_[i]->setIExt(0);
        } else {
          all_neurons_[i]->setIExt(EXT_CURRENT);
        }
      }

      updateOneNeuron(i);
    }

    ++global_clock_;

  }

}


 void Network::updateOneNeuron(unsigned int id_n) {
   bool spike(false);
   spike = all_neurons_[id_n]->update(1);

   /*If the neuron spikes, then we udpate the membrane potential of its post-syn
   synaptic neurons*/
   if (spike) {

     vector<size_t> post;
     //We look for the post-syn neurons and store their index
     for (size_t i(0); i < nb_neurons_; ++i) {
       if (connexions_[id_n][i]) post.push_back(i);
     }

     size_t nb_post(post.size());
     for (size_t i(0); i < nb_post; ++i) {
       assert(all_neurons_[post[i]] != nullptr);
       all_neurons_[post[i]]->receive(D, J);
     }

   }
 }
