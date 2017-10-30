#include "experiment.h"

Experiment::Experiment() : network(new Network())
{
    network->create();
}

Experiment::~Experiment()
{
  delete network;
}

Network* Experiment::getNetwork() const {
  return network;
}

void Experiment::connect() {
  size_t nb_neurons((network->getAllNeurons()).size());
  assert(nb_neurons > 0);

  /*
   * For each neuron, we ramdomly choose 1000 excitatory neurons and 250
   * inhibitory neurons that will target this particular neuron
   */
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> distribEx(indexFirstExcitatoryNeuron, indexLastExcitatoryNeuron);
  uniform_int_distribution<> distribIn(indexFirstInhibitoryNeuron, indexLastInhibitoryNeuron);
  //these indices are found in the Constants.hpp file

// We initialize all the connexions of the neurons in the network
for (size_t i(0); i < nb_neurons; ++i) {

  // This neuron will be "target" by C_EXCI connexions from excitatory neurons
  for (size_t j(0); j < C_EXCI; ++j) {
    int random_index(distribEx(gen));
    network->addConnexion(random_index, i);

    /*
     * Neuron in position i of the vector all_neurons_ have a synaptic connexion
     * to neuron in position random_index :
     * random_index neuron -> i neuron
     * (i is a post-synaptic neuron of neuron random_index)
     */
  }

    // This neuron will be "target" by C_INHI connexions from inhibitory neurons
    for (size_t k(0); k < C_INHI; ++k) {
      int random_index(distribIn(gen));
      network->addConnexion(random_index, i);
    }
  }

  cout << "Network connected." << endl;
}

void Experiment::run(long simulation_time) {
  network->updateNetwork(simulation_time);
}

void Experiment::save_spikes(string file) {
  ofstream out;
  out.open(file);
  out.clear();
     if (out.fail()) {
        cerr << "Error opening the file" << endl;
     } else {
       vector<double> spikeTimes(network->getSpikeTimes());
       vector<size_t> neurons_indexes(network->getNeuronsIndexes());
       double spike_size(spikeTimes.size());
       assert(spike_size == neurons_indexes.size());
       //ostringstream texte;

        for (size_t i(0); i < spike_size; ++i) {
             out << spikeTimes[i]*H << '\t'<< neurons_indexes[i] << '\n';
         }

        //  string potentialAsString = texte.str(); // str() transforms the stream's content into string
        //  out << potentialAsString << endl;
          out.close();
     }
}
