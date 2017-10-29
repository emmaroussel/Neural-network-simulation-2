#ifndef NETWORK_H
#define NETWORK_H

/*!
 * \file network.h
 * \brief Network class
 * \author emma-roussel
 */

#include "Constants.hpp"
#include "neuron.h"
#include <iostream>
#include <vector>
#include <cassert>
#include <random>
#include <map>
using namespace std;


  /*!
   * \class Network
   * \brief class simulating a network of neurons
   *
   * Simulate a network a neurons which interact via connexions.
   * Spiking of neurons are handled by transferring an amplitude response (in mV)
   * to the post-synaptic neurons of the one which has spiked. The network is
   * aware of the connexions and their multiplicity between the neurons. One neuron
   * can have multiple connexions towards the same neuron. A neuron can have
   * connexion(s) with itself.
   */

class Network {
  public :

    //! Constructor
    /*!
     * \param all_neurons list of pointers of neurons which will compose the network
     * With this constructor, the connexions between neurons have to be manually added.
     */
    Network(vector<Neuron*> all_neurons);

    //! Constructor
    /*!
     * Builds a network of N neurons with NE excitatory and NI inhibitory neurons.
     * Connects the neurons : each neuron will receive C_EXCI excitatory and C_INHI
     * inhibitory connexions from ramdomly chosen neurons.
     * N, NE, NI, C_EXCI, C_INHI are constants found in the Constants.hpp file.
     */
    Network();

    //! Destructor
    /*!
     * Delete all the neurons as they were manually allocated when the network
     * was built.
     */
    ~Network();

    //! Getter for the neurons of the network
    /*!
     * \return pointers of all the neurons of the network
     */
    vector<Neuron*> getAllNeurons() const;

    //! Getter for the connexions of neurons in the network
    /*!
     * \return all the connexions between neurons
     */
    vector< vector<int> > getConnexions() const;

    //! Getter for the map of spike times / corresponding neuron
    /*!
     * \return The times where at least one neuron has spiked, and the number(s) of the neuron(s) which has spiked
     */
    map<double, vector<int> > getMap() const;


    //! Add a neuron to the network
    /*!
     * \param n the pointer of a neuron we want to add to the list of neurons of the network
     */
    void addNeuron(Neuron* n);

    //! Add a connexion (unidirectionnal) between 2 neurons
    /*!
     * \param id_n1 index of the pre-synaptic neuron
     * \param id_n2 index of the post-synaptic neuron
     */
    void addConnexion(unsigned int id_n1, unsigned int id_n2);

    //! Delete a connexion (unidirectionnal) between 2 neurons
    /*!
     * \param id_n1 index of the pre-synaptic neuron
     * \param id_n2 index of the post-synaptic neuron
     */
    void deleteConnexion(unsigned int id_n1, unsigned int id_n2);

    //! Update all the neurons of the network in a defined period of time
    /*!
     * Updates each neuron of the network one by one, one (time) step at a time
     * by calling the updateOneNeuron function.
     */
    void updateNetwork();

    //! Update one neuron of the network
    /*!
     * Updates a neuron. If the neuron spikes, then all of the post-synaptic
     * neurons of this neuron will receive an amplitude response which will be
     * stored in their ring buffer. This amplitude response is proportionnal
     * to the number of connexions between this neuron and a post-synaptic neuron.
     * We store the spike time and the number (index) of the neuron in the map attribut.
     */
    void updateOneNeuron(unsigned int id_n);

  private :
    long global_clock_; /*!< global clock */
    vector<Neuron*> all_neurons_; /*!< pointers on the neurons of the network */
    unsigned int nb_neurons_; /*!< total number of neurons in the network */
    vector< vector<int> > connexions_; /*!< connexions between neurons */
    map<double, vector<int> > spike_times_and_neurons_; /*!< map of all spike times linked to which neuron spiked */

};

#endif
