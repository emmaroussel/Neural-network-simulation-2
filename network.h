#ifndef NETWORK_H
#define NETWORK_H

#include "Constants.hpp"
#include "neuron2.h"
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

class Network {
  public :
    //CONSTRUCTOR
    Network();
    ~Network();

    //METHODS
    void addNeuron(Neuron* n);
    void addConnexion(Neuron* n1, Neuron* n2);
    void updateNetwork();
    void updateOneNeuron(Neuron* n);

  private :
    vector<Neuron*> neurons;
    long global_clock_;

};

#endif
