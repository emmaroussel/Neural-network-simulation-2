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
    Network(vector<Neuron*> all_neurons);
    ~Network();

    //METHODS
    void addNeuron(Neuron* n);
    void addConnexion(unsigned int id_n1, unsigned int id_n2);
    void deleteConnexion(unsigned int id_n1, unsigned int id_n2);
    void updateNetwork();
    void updateOneNeuron(unsigned int id_n);

  private :
    long global_clock_;
    vector<Neuron*> all_neurons_;
    unsigned int nb_neurons_;
    vector< vector<bool> > connexions_;

};

#endif
