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
   * \brief Class simulating a network of neurons
   *
   * Simulates a network of neurons which interact via connexions.
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
     * The connexions between neurons have to be manually added (method connect()).
     */
    Network(vector<Neuron*> all_neurons);

    //! Constructor
    /*!
     * Create an empty network.
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

    //! Getter for the targets of each neuron
    /*!
     * \return list targets (post-synaptic neurons) for each neuron
     */
    vector< vector<size_t> > getTargets() const;

     //! Getter for the neurons which have spiked
     /*!
      * \return the indexes of the neurons which have spiked
      */
    vector<size_t>  getNeuronsIndexes() const;

    //! Getter for the spike times
    /*!
     * \return the spike times
     */
    vector<double> getSpikeTimes() const;

    //! Getter for the number of neurons
    /*!
     * \return the number of neurons in the network
     */
    size_t getNbNeurons() const;

    //! Create all the neurons in the network
    /*
     * Fills the network with N neurons : NE excitatory and NI inhibitory neurons.
     * N, NE, NI are constants found in the Constants.hpp file.
     */
    void create();

    //! Add a neuron to the network
    /*!
     * \param n the pointer of a neuron we want to add to the list of neurons of the network
     */
    void addNeuron(Neuron* n);

    //! Add a connexion (unidirectionnal) between 2 neurons
    /*!
     * \param id_n1 index of the pre-synaptic neuron
     * \param id_n2 index of the post-synaptic neuron
     * \param weight the weight of the connexion
     */
    void addConnexion(unsigned int id_n1, unsigned int id_n2);

    //! Update all the neurons of the network in a defined period of time
    /*!
     * Updates each neuron of the network one by one, one (time) step at a time
     * by calling the updateOneNeuron function.
     */
    void updateNetwork(long simulation_time);

    //! Update one neuron of the network
    /*!
     * Updates a neuron. If the neuron spikes, then all of the post-synaptic
     * neurons of this neuron will receive a response which will be
     * stored in their ring buffer.
     * We store the spike time and the number (index) of the neuron in the spike_times_
     * and neurons_idx_ attributs.
     */
    void updateOneNeuron(unsigned int id_n);

  private :
    long global_clock_; /*!< global clock */
    vector<Neuron*> all_neurons_; /*!< pointers on the neurons of the network */
    size_t nb_neurons_; /*!< total number of neurons in the network */
    vector<double> spike_times_; /*!< all the spike times */
    vector<size_t> neurons_idx_; /*!< indexes of the neurons which have spiked */
    vector< vector<size_t> > targets_; /*!< gathers the post-synaptic neurons for each neuron*/

};

#endif
