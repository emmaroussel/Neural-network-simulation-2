#ifndef CONSTANTS_NEURON_HPP
#define CONSTANTS_NEURON_HPP

//Numerical constants
double const T_START = 0;
double const T_STOP = 500; //in ms
double const H = 0.1; //path of time in ms (h)
double const EXT_CURRENT = 1.01; //external current in pA
double const TAU = 20; //in ms
double const REFRAC_TIME = 2; //refractory period in ms
double const RESISTANCE = 20;
double const V_INI = -70; //initial potential
double const V_THRS = 20; //V Threshold, in mV
double const V_REFRAC = 0; //potential during refractory period, in mV
double const V_RESET = 0; //potential after the refractory period
//V_RESET must be below V_THRS to prevent spiking continuously

double const J = 0.2; //in mV

double const EPSILON = 0.1;

#endif
