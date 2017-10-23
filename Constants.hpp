#ifndef CONSTANTS_NEURON_HPP
#define CONSTANTS_NEURON_HPP

//Numerical constants
double const T_START = 0;
double const T_STOP = 500; // simulation time in ms
double const H = 0.1;  // integration time step in ms
double const EXT_CURRENT = 1.0; // external current in pA
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
int const D = 1.5/H; // synaptic delay already in steps (-> 1.5ms)
double const EPSILON = 0.1; // constant to compare double values

#endif
