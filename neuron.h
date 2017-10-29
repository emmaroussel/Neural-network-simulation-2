#ifndef NEURON1_H
#define NEURON1_H

/*!
 * \file neuron.h
 * \brief Neuron class
 * \author emma-roussel
 */

#include "Constants.hpp"
#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include <cassert>
#include <random>
using namespace std;

/*!
 * \class Neuron
 * \brief Class simulating a neuron
 *
 * Simulate a neuron which can be either excitatory or inhibitory. The difference
 * between these two type of neurons is the sign and value of their response amplitude.
 * The neuron can be updated during a period of time. This will mainly update its
 * membrane potential and handle the behaviour of the neuron if it exceeds the
 * membrane potential threshold. 
 */
class Neuron {
  public :
    //! Constructor
    Neuron();

    //! Constructor with initial membrane potential value
    /*!
     * \param potential the initial membrane potential value
     */
    Neuron(double potential);

    //! Constructor with type of the neuron
    /*!
     * \param excitatory the type of the neuron (excitatory : true, inhibitory : false)
     */
    Neuron(bool excitatory);

    //! Constructor with type of the neuron and possibility to shut down the background noise
    /*!
     * \param excitatory the type of the neuron (excitatory : true, inhibitory : false)
     * \param background_noise true : with background noise, false : without
     * Shutting down the background_noise is useful for testing the good behaviour
     * of the functions (with test_neuron.cpp)
     */
    Neuron(bool excitatory, bool background_noise);

    //! Destructor
    ~Neuron();


    //! Getter for the membrane potential
    /*!
     * \return the membrane potential value
     */
    double getMembranePotential() const;

    //! Getter for the number of spikes
    /*!
     * \return the total number of spikes
     */
    long getNbSpikes() const;

    //! Getter for the time of the last spike
    /*!
     * \return the time of the last spike
     */
    long getSpikeTime() const;

    //! Getter for all the membrane potentials
    /*!
     * \return all the membrane potential values
     */
    vector<double> getAllMembranePotentials() const;

    //! Getter for J (post-synaptic potential amplitude)
    /*!
     * \return the post-synaptic potential amplitude of the neuron
     */
    double getJ() const;


    //! Setter for the membrane potential
    /*!
     * \param potential the new membrane potential of the neuron
     */
    void setMembranePotential(double potential);

    //! Setter for the external current
    /*!
     * \param current the new external current value
     */
    void setIExt(double current);

    //! Method to add a membrane potential to all the membrane potentials
    /*!
     * \param potential potential value which is going to be stored
     */
    void updateAllMembranePotentials(double potential);

    //! Update the membrane potential
    /*!
     * Computes the new membrane potential considering the external current,
     * the spike(s) the neuron received (from its pre-synaptic neurons),
     * the spikes from possible external connexion(s) (simulated with a
     * poisson distribution).
     */
    void updateMembranePotential();

    //! Update the neuron
    /*!
     * \param steps the number of time steps during which we want to update the neuron
     * \return if the neuron has spiked (true)
     * If the membrane potential reached/exceeded the membrane potential threshold,
     * the neuron spikes and is set to refractory, and it will stay refractory
     * until the refractory period is passed.
     * Otherwise, we update the membrane potential.
     * We update the ring buffer.
     */
    bool update(long steps);

    //! The neuron receives a spike from another neuron
    /*!
     * \param delay the number of time step before the neuron responses to the incoming spike
     * \param j total response amplitude (if there are multiple connexions between
     * the neuron which has spiked and this neuron, the response amplitude will be
     * multiplied by the number of connexions between these two neurons).
     * 
     * Stores the amplitude response in a ring buffer at the correct position
     * (taking into consideration the delay)
     */
    void receive(int delay, double j);

    //! Update the ring buffer
    /*!
     * It moves the read-out index of one step. This update function is called
     * each time we update the neuron for one step. As the response amplitudes
     * are stored in this buffer at a precise delay, since we move the read-out
     * index simultaneously with time of simulation (local one), when we compute
     * the membrane potential we will add the correct value of response amplitude.
     */
    void updateRingBuffer();

  private :
    double membrane_potential_; //!< membrane potential */
    double i_ext_; //!< external current */
    long nb_spikes_; //!< number of spikes */
    long spike_time_; //!< time of the last spike */
    bool refractory_; //!< true : when the neuron is refractory */
    long clock_; //!< local clock of the neuron */

    //! Refractory steps
    /*!
     * Will be incremented when the neuron is refractory to check if the
     * refractory period is passed or not, if so it will be put to 0.
     */
    long refractory_steps_;

    vector<double> allMembranePotentials_; //!< stores membrane potential of each time step */

    //! Ring buffer
    /*!
     * Stores the incoming spikes at different steps.
     * We assume the delay here is maximum equal to 15 steps (see Constants.hpp)
     */
    array<double, D+1> ring_buffer_;

    size_t rb_index_; //!< ring buffer read-out index */
    bool excitatory_; //!< if true then the neuron is excitarory_, otherwise : inhibitory */

    //! Response amplitude of this neuron
    /*!
     * When this neuron will spike, it will affect each of its post-synaptic neurons
     * with this value (without considering the number of connexions between this neuron
     * and each of its post-synaptic neuron, this is done by the Network which is aware of
     * the connexions between the neurons).
     */
    double j_;

    //! Presence of background noise
    /*!
     * Allows to check the good behaviour of the functions with or without
     * this background_noise.
     */
    bool background_noise_;

};


#endif
