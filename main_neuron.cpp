#include "neuron.h"
#include "network.h"
#include "experiment.h"
#include "gtest/gtest.h"
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <time.h>

int main() {
  //To measure the time of execution
  clock_t start;
  int execution_time;
  start = clock();

  Experiment experiment; // Creates a network with N neurons
  experiment.connect(); // Connects these neurons
  experiment.run(1000); //run for 1000 ms
  experiment.save_spikes("spikes_times_neurons.txt"); // Saves the spike times and corresponding neurons

  clock_t stop(clock());
  execution_time = (stop - start)/(CLOCKS_PER_SEC/1000);
  cout << '(' << execution_time << "ms total)" << endl;

  /*****************************************************************************/
    void print(string name, Neuron neuron1);
    // We can use this function to print all the membrane potential values
    // for each time step of a simulation for one neuron

  return 0;
}

void print(string name, Neuron neuron1) {
  ofstream out;
  out.open(name);
  out.clear();
  if (out.fail()) {
      cerr << "Erreur lecture fichier" << endl;
  } else {
      vector<double> potential_values(neuron1.getAllMembranePotentials());
      ostringstream texte;

      for (unsigned int i(0); i < potential_values.size(); ++i) {
          texte << potential_values[i] << endl;
      }

   string potentialAsString = texte.str(); //! str() transforms the stream's content into string
   out << potentialAsString << endl;
   out.close();
  }
}
