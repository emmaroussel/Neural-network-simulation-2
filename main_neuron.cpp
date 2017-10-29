#include "neuron.h"
#include "network.h"
#include "gtest/gtest.h"
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <time.h>

int main() {
  clock_t start;
  int execution_time;
  start = clock();

  Network network;
  clock_t stop1(clock());
  cout << "Network building done. (" << stop1/(CLOCKS_PER_SEC/1000) << "ms)" << endl;
  
  network.updateNetwork();
  clock_t stop2(clock() - stop1);
  cout << "Network updatating done. (" << stop2/(CLOCKS_PER_SEC/1000) << "ms)" << endl;

/*****************************************************************************/
  void print(string name, Neuron neuron1);
  /*
   * We print the membrane potential values of the 2 neurons in files.
   */
print("membrane_potential_values.txt", *(network.getAllNeurons()[0]));
  print("membrane_potential_values2.txt", *(network.getAllNeurons()[1]));

/*****************************************************************************/
   ofstream out;
   out.open("spikes_and_neurons_values.txt");
   out.clear();
      if (out.fail()) {
         cerr << "Erreur lecture fichier" << endl;
      } else {
         map<double, vector<int> > spikes_and_neurons(network.getMap());
         ostringstream texte;
         texte << "Spike times" << " " << setw(4) << "|"
               << " " << setw(4) << "Neuron n°" << endl;
         for (map<double, vector<int> >::iterator i(spikes_and_neurons.begin());
              i != spikes_and_neurons.end(); ++i) {
                texte << i->first << " " << setw(13);
                for (auto neuron_number : i->second) {
                  texte << setw(2) << " " << neuron_number;
                }
                texte << endl;
                texte << endl;
              }

           string potentialAsString = texte.str(); // str() transforms the stream's content into string
           out << potentialAsString << endl;
           out.close();
      }

  clock_t stop(clock());
  execution_time = (stop - start)/(CLOCKS_PER_SEC/1000);
  cout << '(' << execution_time << "ms total)" << endl;

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
