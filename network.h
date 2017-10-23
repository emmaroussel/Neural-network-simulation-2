#ifndef NETWORK_H
#define NETWORK_H

/*!
 * \file network.h
 * \brief Network class
 * \author emma-roussel
 * \version 0.5
 */

#include "Constants.hpp"
#include "neuron2.h"
#include <iostream>
#include <vector>
#include <cassert>
#include <random>
#include <map>
using namespace std;


  /*! \class Network
   * \brief class simulating a network of neurons
   *
   * Simulate a network a neurons which interact via connexions.
   * Spiking of neurons are handled by transferring an amplitude spike
   * to the connected neurons.
   */

class Network {
  public :
    //! Constructor
    Network(vector<Neuron*> all_neurons);
    //! Constructor
    Network();
    //! Destructor
    ~Network();

    //! Getter for the neurons of the network
    vector<Neuron*> getAllNeurons() const;
    //! Getter for the map of spike times / corresponding neuron
    map<double, vector<int> > getMap() const;

    //! Add a neuron to the network
    void addNeuron(Neuron* n);
    //! Add a connexion (unidirectionnal) between 2 neurons
    void addConnexion(unsigned int id_n1, unsigned int id_n2);
    //! Delete a connexion (unidirectionnal) between 2 neurons
    void deleteConnexion(unsigned int id_n1, unsigned int id_n2);
    //! Update all the neurons of the network in a defined period of time
    void updateNetwork();
    //! Update one neuron of the network
    void updateOneNeuron(unsigned int id_n);

  private :
    long global_clock_; /*!< global clock */
    vector<Neuron*> all_neurons_; /*!< pointers on the neurons of the network */
    unsigned int nb_neurons_; /*!< total number of neurons in the network */
    vector< vector<int> > connexions_; /*!< connexions between neurons */
    map<double, vector<int> > spike_times_and_neurons_; /*!< map of all spike times linked to which neuron spiked */

};

#endif
