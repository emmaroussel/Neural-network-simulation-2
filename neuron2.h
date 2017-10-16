#ifndef NEURON1_H
#define NEURON1_H

#include "Constants.hpp"
#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include <cassert>
using namespace std;

class Neuron {
  public :
    //CONSTRUCTORS
    Neuron();
    Neuron(double potential);

    //GETTERS
    double getMembranePotential() const;
    long getNbSpikes() const;
    long getSpikeTime() const;
    vector<double> getAllMembranePotentials() const;
    vector<Neuron*> getPostSynNeuron() const;

    //SETTER
    void setMembranePotential(double potential);
    void setIExt(double current);
    void updateAllMembranePotentials(double potential);
    void setPostSynNeuron(Neuron* n);

    //METHODS
    void updateMembranePotential(double current, double h, double tau, double resistance);
    bool update(long steps);
    void receive(int delay, double j);
    void updateRingBuffer();
    void increaseIndex();

  private :
    double membrane_potential_;
    double i_ext_;
    long nb_spikes_;
    long spike_time_;
    bool refractory_;
    long clock_;
    long refractory_steps_;
    vector<double> allMembranePotentials_;

    /*Tableau de l'ensemble des neurones post-synaptiques*/
    vector<Neuron*> targets;
    array<double, 15> ring_buffer_;
    /*stores the incoming spikes at ≠ steps
    We assume the delay here is maximum equal to 15 steps*/
    size_t rb_index_; //ring buffer index for read-out

};


#endif
