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
 */

TEST (NeuronTest, MembranePotential) {
  Neuron neuron(true, false); // Excitatory neuron with no background noise
  EXPECT_EQ(0, neuron.getMembranePotential());
  neuron.setIExt(1.0);
  neuron.update(1);
  EXPECT_EQ(RESISTANCE*(1-exp(-H/TAU)), neuron.getMembranePotential());
}


TEST (NeuronTest, SpikeTimes) {
  Neuron neuron(true, false); // Excitatory neuron with no background noise
  neuron.setIExt(1.01);
  // We know that the spikes times are at 92.5ms, 186.9ms, 281.3ms
  // Before the first spike, number of spikes should be 0
  neuron.update(924);
  EXPECT_EQ(0, neuron.getNbSpikes());
  // Just after the spike, spike number should be 1, and membrane potential 0.0
  neuron.update(1);
  EXPECT_EQ(0.0, neuron.getMembranePotential());
  EXPECT_EQ(1, neuron.getNbSpikes());

  // We check for the second spike
  neuron.update(943); // (1869-(925+1)
  EXPECT_EQ(1, neuron.getNbSpikes());
  neuron.update(1);
  EXPECT_EQ(0.0, neuron.getMembranePotential());
  EXPECT_EQ(2, neuron.getNbSpikes());
}

TEST (NeuronTest, PositiveInput) {
  Neuron neuron(true, false); // Excitatory neuron with no background noise
  neuron.setIExt(1.0);

  // Update one step
  neuron.update(1);
  EXPECT_EQ(RESISTANCE*(1-exp(-H/TAU)), neuron.getMembranePotential());

  // Update many steps
  neuron.update(10000);
  // As the external current is 1.0, membrane potential should tend to 20 but
  // should not reach it. The neuron should not spike
  EXPECT_EQ(0, neuron.getNbSpikes());
  EXPECT_GT(1E-3, fabs(19.999 - neuron.getMembranePotential()));

  // When external current is 0, membrane potential should tend to 0
  neuron.setIExt(0.0);
  neuron.update(2000);
  EXPECT_NEAR(0, neuron.getMembranePotential(), 1e-3);

}

TEST (NeuronTest, NegativeInput) {
  Neuron neuron(true, false); // Excitatory neuron with no background noise
  neuron.setIExt(-1.0);

  // Update one step
  neuron.update(1);
  EXPECT_EQ(-RESISTANCE*(1-exp(-H/TAU)), neuron.getMembranePotential());

  // Update many steps
  neuron.update(10000);
  // As the external current is -1.0, membrane potential should tend to -20
  EXPECT_GT(1E-3, fabs(-19.999 - neuron.getMembranePotential()));

  // When external current is 0, membrane potential should tend to 0
  neuron.setIExt(0.0);
  neuron.update(2000);
  EXPECT_NEAR(0, neuron.getMembranePotential(), 1e-3);

}

TEST (TwoNeuronsTest, SpikeTimeDelay) {
  vector<Neuron*> all_neurons;
  // Excitatory neurons with no background noise
  all_neurons.push_back(new Neuron(true, false));
  all_neurons.push_back(new Neuron(true, false));
  all_neurons[0]->setMembranePotential(20); // When we will update it, it will spike
  all_neurons[1]->setMembranePotential(0);

  all_neurons[0]->setIExt(1.01);

  //! We have 2 neurons in the network
  Network network(all_neurons);
  network.addConnexion(0,1);

  network.updateOneNeuron(0); // update the first neuron (all_neurons[0])
  double v_ini(0); // membrane potential of all_neurons[1] when all_neurons[0] is spiking
  double v_fin(0); // membrane potential of all_neurons[1] when receiving J (after the delay)
  for (size_t i(0); i < D+1; ++i) {
      network.updateOneNeuron(1);
      if (i == 0) v_ini = (network.getAllNeurons()[1])->getMembranePotential();
      if (i == D) v_fin = (network.getAllNeurons()[1])->getMembranePotential();
  }

  double expected_value(all_neurons[0]->getJ()); // Equal to the response amplitude of the first neuron
  EXPECT_NEAR(v_fin, v_ini, expected_value);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
