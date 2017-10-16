#include "neuron2.h"
#include "network.h"
#include <fstream>
#include <sstream>

int main() {

  size_t nb_neurons(2); //can be changed if we want more neurons

  vector<Neuron*> all_neurons;
  for (size_t i(0); i < nb_neurons; ++i) {
    all_neurons.push_back(new Neuron);
  }

  //pour l'instant on veut que potentiel memb. de neuron2 = 0
  all_neurons[1]->setMembranePotential(0);

  Network network(all_neurons);

  //Adding connexions between neurons -> can be done in the Network via a method !
  unsigned int nb_connexions_per_neuron(0);
  if (nb_neurons >= 10) { //laisse ça comme ça pour l'instant car que 2 neurones
    /*Each neuron receives input from 10% of the other neurons*/
    nb_connexions_per_neuron = 0.1*nb_neurons; //total connexions to be received
  } else {
    nb_connexions_per_neuron = 1;
  }

  for (size_t i(0); i < nb_neurons; ++i) {
    /*We randomly choose a neuron to be a pre-synaptic neuron of *all_neurons_[i]
    until the total number of connexion for *all_neurons_[i] is reached*/
    unsigned int nb_co(0);
    unsigned int j(0);
    do {
      //->random choice of j, avec j != i
      if (i != j) {
        network.addConnexion(j, i);
        //all_neurons_[i] is a post-synaptic neuron of all_neurons_[j]
        ++nb_co;
      } else {
        j = 1; //à enlever quand j sera choisi randomly
      }
    } while (nb_co < nb_connexions_per_neuron);

  }

  network.deleteConnexion(1,0);
  /*delete connexion from neuron[1] to neuron[0],
  just now because we have 2 neurons and we want an unidirectionnal connexion*/

  network.updateNetwork();

/*****************************************************************************/
  void print(string name, Neuron neuron1);

  print("membrane_potential_values.txt", *all_neurons[0]);
  print("membrane_potential_values2.txt", *all_neurons[1]);

/*****************************************************************************/

  for (size_t i(0); i < nb_neurons; ++i) {
    delete all_neurons[i];
  }
  all_neurons.clear();

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
