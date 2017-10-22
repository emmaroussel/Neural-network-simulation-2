#include <iostream>
#include <vector>
#include "gtest/gtest.h"
#include "neuron2.h"
#include "network.cpp"
#include "Constants.hpp"
using namespace std;

/*!
 * \file test_neuron.cpp
 * \brief Tests
 * \author emma-roussel
 * \version 0.1
 */

TEST (NeuronTest, MembranePotential) {
  Neuron neuron(0);
  neuron.setIExt(1.0);
  neuron.update(1);
  EXPECT_EQ(RESISTANCE*(1-exp(-H/TAU)), neuron.getMembranePotential());
}

TEST (NeuronTest, SpikeTimeDelay) {
  vector<Neuron*> all_neurons;
  all_neurons.push_back(new Neuron);
  all_neurons.push_back(new Neuron);
  all_neurons[0]->setMembranePotential(20); //! When we will update it, it will spike
  all_neurons[1]->setMembranePotential(0);

  all_neurons[0]->setIExt(1.01);

  //! We have 2 neurons in the network
  Network network(all_neurons);
  network.addConnexion(0,1);

  network.updateOneNeuron(0); //! update the first neuron (all_neurons[0])
  double v_ini(0); //! membrane potential of all_neurons[1] when all_neurons[0] is spiking
  double v_fin(0); //! membrane potential of all_neurons[1] when receiving J (after the delay)
  for (size_t i(0); i < D+1; ++i) {
      network.updateOneNeuron(1);
      if (i == 0) v_ini = (network.getAllNeurons()[1])->getMembranePotential();
      if (i == D) v_fin = (network.getAllNeurons()[1])->getMembranePotential();
  }

  EXPECT_NEAR(v_fin, v_ini, 0.2);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
