#ifndef CONSTANTS_NEURON_HPP
#define CONSTANTS_NEURON_HPP

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
/*
 * V_RESET must be below V_THRS to prevent spiking continuously
 */
double const J = 0.1; // spike response amplitude in mV
double const g = 5; // ratio JI/JE
double const JE = 0.1; // spike response amplitude for excitatory neurons in mV
double const JI = -g*J; // spike response amplitude for inhibitory neurons in mV
int const D = 1.5/H; // synaptic delay already in steps (-> 1.5ms)

double const V_TH = 0.01; // using the formula in Brunel's paper
double const V_EXT = 2*V_TH; // firing external rate
int const N = 12500; // number of neurons
int const N_EXCI = 10000; // number of excitatory neurons
int const N_INHI = 2500; // number of excitatory neurons
int const C_EXCI = 1000; // Number of excitatory connexions for 1 neuron (10% * N_EXCI)
//C_EXT is equal to C_EXCI
int const C_INHI = 250; // Number of inhibitory connexions for 1 neuron (10% * N_INHI)

double const EPSILON = 0.1; // constant to compare double values

#endif
