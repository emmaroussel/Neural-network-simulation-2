#include "network.h"

//CONSTRUCTOR
Network::Network() : global_clock_(0)
{}

//DESTRUCTOR
Network::~Network()
{}

//METHODS
void Network::addNeuron(Neuron* n) {
  assert(n != nullptr);
  neurons.push_back(n);
}

void Network::addConnexion(Neuron* n1, Neuron* n2) {
    assert(n1 != nullptr);
    assert(n2 != nullptr);
    n1->setPostSynNeuron(n2);
}

void Network::updateNetwork() {

  size_t t_stop(T_STOP/H); //in terms of steps
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

    for (size_t i(0); i < neurons.size(); ++i) {
      assert(neurons[i] != nullptr);

      neurons[i]->setIExt(0); //à enlever là c'est juste pour que l'input current du neuron2 soit = 0
      if (i == 0) { //à enlever c'est juste pour que input current neuron2=0
        //We update the input current for the neuron 1
        if (zero) {
          neurons[i]->setIExt(0);
        } else {
          neurons[i]->setIExt(EXT_CURRENT);
        }
      }

      updateOneNeuron(neurons[i]);
      }

    ++global_clock_;

  }

}


 void Network::updateOneNeuron(Neuron* n) {
   bool spike(false);
   spike = n->update(1);

   /*If the neuron spikes, then we udpate the membrane potential of its post-syn
   synaptic neurons*/
   if (spike) {

     size_t nbPostSyn((n->getPostSynNeuron()).size()); //nb of post-syn neurons of n

     for (size_t i(0); i < nbPostSyn; ++i) {
       assert((n->getPostSynNeuron())[i] != nullptr);
       (n->getPostSynNeuron())[i]->receive(D, J);
     }

   }
 }
