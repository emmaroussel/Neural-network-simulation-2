#include "neuron2.h"
#include "network.h"
#include <fstream>
#include <sstream>

int main() {
  Neuron neuron1;
  Neuron neuron2(0);

  Network network;
  network.addNeuron(&neuron1);
  network.addNeuron(&neuron2);
  //Neuron2 is a post-synaptic neuron of neuron1
  network.addConnexion(&neuron1,&neuron2);

  network.updateNetwork();

/*****************************************************************************/
  void print(string name, Neuron neuron1);

  print("membrane_potential_values.txt", neuron1);
  print("membrane_potential_values2.txt", neuron2);

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

   string potentialAsString = texte.str(); //str() transforms the stream's content into string
   out << potentialAsString << endl;
   out.close();
  }
}
