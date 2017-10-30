#include <iostream>
#include <vector>
#include "gtest/gtest.h"
#include "neuron.h"
#include "network.h"
#include "Constants.hpp"
using namespace std;

/*!
 * \file test_neuron.cpp
 * \brief Tests
 * \author emma-roussel
 */

//! Tests correct computation of the membrane potential
TEST (NeuronTest, MembranePotential) {
  Neuron neuron(true, false); // Excitatory neuron with no background noise
  EXPECT_EQ(0, neuron.getMembranePotential());
  neuron.setIExt(1.0);
  neuron.update(1);
  EXPECT_EQ(RESISTANCE*(1-exp(-H/TAU)), neuron.getMembranePotential());
}

//! Tests correct behaviour of membrane potential by checking spike times
TEST (NeuronTest, SpikeTimes) {
  Neuron neuron(true, false); // Excitatory neuron with no background noise
  neuron.setIExt(1.01);
  // We know that the spikes times are at 92.5ms, 186.9ms, 281.3ms
  // Before the first spike, the number of spikes should be 0
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

//! Tests correct behaviour of membrane potential with positive input (external current)
TEST (NeuronTest, PositiveInput) {
  Neuron neuron(true, false); // Excitatory neuron with no background noise
  neuron.setIExt(1.0);

  // Update one step
  neuron.update(1);
  EXPECT_EQ(RESISTANCE*(1-exp(-H/TAU)), neuron.getMembranePotential());

  // Update many steps
  neuron.update(10000);
  // As the external current is 1.0, membrane potential should tend to 20 but
  // should not reach it. The neuron should not spike.
  EXPECT_EQ(0, neuron.getNbSpikes());
  EXPECT_GT(1E-3, fabs(19.999 - neuron.getMembranePotential()));

  // When external current is 0, membrane potential should tend to 0.
  neuron.setIExt(0.0);
  neuron.update(2000);
  EXPECT_NEAR(0, neuron.getMembranePotential(), 1e-3);

}

//! Tests correct behaviour of membrane potential with negative input (external current)
TEST (NeuronTest, NegativeInput) {
  Neuron neuron(true, false); // Excitatory neuron with no background noise
  neuron.setIExt(-1.0);

  // Update one step
  neuron.update(1);
  EXPECT_EQ(-RESISTANCE*(1-exp(-H/TAU)), neuron.getMembranePotential());

  // Update many steps
  neuron.update(10000);
  // As the external current is -1.0, membrane potential should tend to -20.
  EXPECT_GT(1E-3, fabs(-19.999 - neuron.getMembranePotential()));

  // When external current is 0, membrane potential should tend to 0.
  neuron.setIExt(0.0);
  neuron.update(2000);
  EXPECT_NEAR(0, neuron.getMembranePotential(), 1e-3);

}

//! Tests correct transmission of spikes (with correct delay) between two neurons
TEST (TwoNeuronsTest, SpikeTimeDelay) {
  vector<Neuron*> all_neurons;
  // Excitatory neurons with no background noise
  all_neurons.push_back(new Neuron(true, false));
  all_neurons.push_back(new Neuron(true, false));
  all_neurons[0]->setMembranePotential(20); // When we will update it, it will spike
  all_neurons[1]->setMembranePotential(0);

  all_neurons[0]->setIExt(1.01);

  // We create a network with 2 neurons
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

//! Tests correct number of connexions of a neuron in the network (of 12500 neurons)
TEST(NetworkTest, NumberConnexionsPerNeuron) {
  /*
   * Checking that a neuron actually has C_EXCI and C_INHI connexions
   * This means this neuron receives C_EXCI connexions FROM excitatory neurons
   * and C_INHI connexions FROM inhibitory neurons.
   */

  Network network; //We create a network with N neurons (N is defined in Constants.hpp)

  //We check the number of connexions for the first neuron (index = 0) for example
  int nb_exci_co(0); //number of excitatory connexions
  int nb_inhi_co(0); //number of inhibitory connexions
  size_t nb_neurons(network.getAllNeurons().size());

  vector< vector<size_t> > targets(network.getTargets());

    for (size_t i(0); i < nb_neurons; ++i) {
      size_t row_size(targets[i].size());
      for (size_t j(0); j < row_size; ++j) {
        if (targets[i][j] == 0) { //because we are looking for the connexions targeting neuron 0
          if (i <= indexLastExcitatoryNeuron) nb_exci_co += 1;
          if ((i > indexLastExcitatoryNeuron)and(i <= indexLastInhibitoryNeuron)) {
            nb_inhi_co += 1;
          }
        }
      }
    }


  EXPECT_EQ(nb_exci_co, C_EXCI);
  EXPECT_EQ(nb_inhi_co, C_INHI);

}

//! Verifies that the weight of excitatory neurons are positive
TEST(NetworkTest, ExcitatoryWeight) {
  Network network;
  vector<Neuron*> all_neurons(network.getAllNeurons());
  bool positive_weight(true);
  for (size_t i(0); i <= indexLastExcitatoryNeuron; ++i) {
    if (all_neurons[i]->getJ() < 0) positive_weight = false;
  }

  EXPECT_TRUE(positive_weight);
}

//! Verifies that the weight of inhibitory neurons are negative
TEST(NetworkTest, InhibitoryWeight) {
  Network network;
  vector<Neuron*> all_neurons(network.getAllNeurons());
  bool negative_weight(true);
  for (size_t i(indexFirstInhibitoryNeuron); i <= indexLastExcitatoryNeuron; ++i) {
    if (all_neurons[i]->getJ() > 0) negative_weight = false;
  }

  EXPECT_TRUE(negative_weight);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
