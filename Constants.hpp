#ifndef CONSTANTS_NEURON_HPP
#define CONSTANTS_NEURON_HPP

#include <cmath>

//Numerical constants
double const T_START = 0;
double const T_STOP = 50; // simulation time in ms
double const H = 0.1;  // integration time step in ms
double const EXT_CURRENT = 0.0; // external current in pA
double const TAU = 20; // membrane time constant in ms
double const REFRAC_TIME = 2; // refractory period in ms
double const REFRAC_STEPS = REFRAC_TIME/H; // number of steps in refractory period
double const RESISTANCE = 20; // membrane resistance
double const V_INI = 0; // initial potential in mV
double const V_THRS = 20; // spike threshold
double const V_REFRAC = 0; // membrane potential during refractory period in mV
double const V_RESET = 0; // membrane potential after refractory period in mV
// V_RESET must be below V_THRS to prevent spiking continuously

double const C1 = exp(-H/TAU); // constant to comput the membrane potential
double const C2 = RESISTANCE*(1-C1); // constant to comput the membrane potential

double const J = 0.1; // spike response amplitude in mV
double const g = 5; // ratio JI/JE
double const JE = 0.1; // spike response amplitude for excitatory neurons in mV
double const JI = -g*J; // spike response amplitude for inhibitory neurons in mV
int const D = 1.5/H; // synaptic delay already in steps (-> 1.5ms)

double const V_TH = 0.01; // firing rate computed by using the formula in Brunel's paper
double const V_EXT = 2*V_TH; // firing external rate

int const N = 12500; // number of neurons
int const N_EXCI = 0.8*N; // number of excitatory neurons
int const N_INHI = 0.2*N; // number of excitatory neurons
int const C_EXCI = 0.1*N_EXCI; // number of excitatory connexions for 1 neuron (10% * N_EXCI)
int const C_EXT = C_EXCI;
int const C_INHI = 0.1*N_INHI; // number of inhibitory connexions for 1 neuron (10% * N_INHI)

//First index of the vector gathering the neurons (in Network)
int const indexFirstExcitatoryNeuron = 0;
/*
 * Because we first add all the excitatory neurons in the vector of neurons (in Network),
 * these excitatory neurons are from the first index to the N_EXCI one ; since we start
 * the vector from index 0 -> the last excitatory neuron will be at the N_EXCI-1 index.
 */
int const indexLastExcitatoryNeuron = N_EXCI - 1;

/*
 * Index for the first inhibitory neuron, because we add all the inhibitory neurons at once
 * after adding the excitatory ones, the first inhibitory neuron will be at N_EXCI index.
 */
int const indexFirstInhibitoryNeuron = N_EXCI;

//Index for the last inhibitory neuron = last index of the vector of neurons
int const indexLastInhibitoryNeuron = N - 1;

#endif
