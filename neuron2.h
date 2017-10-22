#ifndef NEURON1_H
#define NEURON1_H

/*!
 * \file neuron.h
 * \brief Neuron class
 * \author emma-roussel
 * \version 0.5
 */

#include "Constants.hpp"
#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include <cassert>
using namespace std;

class Neuron {
  public :
    //! Constructor
    Neuron();
    //! Constructor with initial membrane potential value
    Neuron(double potential);

    //! Destructor
    ~Neuron();

    //! Getter for the membrane potential
    double getMembranePotential() const;
    //! Getter for the number of spikes
    long getNbSpikes() const;
    //! Getter for the time of the last spike
    long getSpikeTime() const;
    //! Getter for all the membrane potentials
    vector<double> getAllMembranePotentials() const;

    //! Setter for the membrane potential
    void setMembranePotential(double potential);
    //! Setter for the external current
    void setIExt(double current);
    //! Method to add a membrane potential to all the membrane potentials
    void updateAllMembranePotentials(double potential);


    void updateMembranePotential();
    //! Update the neuron
    bool update(long steps);
    //! Neuron receive a spike from another neuron
    void receive(int delay, double j);
    void updateRingBuffer();

  private :
    double membrane_potential_; /*!< membrane potential */
    double i_ext_; /*!< external current */
    long nb_spikes_; /*!< number of spikes */
    long spike_time_; /*!< time of the last spike */
    bool refractory_; /*!< true : when the neuron is refractory */
    long clock_; /*!< local clock of the neuron */
    long refractory_steps_;
    /*! will be incremented when neuron is refractory to check if the
     * refractory period is passed or not, if so it will be put to 0
     */
    vector<double> allMembranePotentials_; /*!< stores membrane potential of each step */

    array<double, D+1> ring_buffer_; /*!< ring buffer*/
    /*! Stores the incoming spikes at different steps.
     * We assume the delay here is maximum equal to 15 steps (see Constants.hpp)
     */
    size_t rb_index_; /*!< ring buffer index for read-out */

};


#endif
