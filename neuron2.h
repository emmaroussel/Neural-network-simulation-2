#ifndef NEURON1_H
#define NEURON1_H

#include "Constants.hpp"
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Neuron {
  public :
    //CONSTRUCTORS
    Neuron();

    //GETTERS
    double getMembranePotential() const;
    long getNbSpikes() const;
    long getSpikeTime() const;
    vector<double> getAllMembranePotentials() const;
    bool isRefractory() const;
    Neuron* getPostSyn();

    //SETTER
    void setMembranePotential(double potential);
    void setIExt(double current);
    void updateAllMembranePotentials(double potential);
    void setRefractory(bool state);
    void setPostSyn(Neuron* n);

    //METHODS
    void updateMembranePotential(double current, double h, double tau, double resistance);
    bool update(long steps);
    void receive(double j);

  private :
    double membrane_potential_;
    double i_ext_;
    long nb_spikes_;
    long spike_time_;
    bool refractory_;
    long clock_;
    long refractory_steps_;
    vector<double> allMembranePotentials_;

    Neuron* post_syn_;
};


#endif
