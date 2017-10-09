#include "neuron2.h"
#include <fstream>
#include <sstream>

int main() {

  Neuron neuron1;
  Neuron neuron2;
  Neuron neuron3;
  neuron1.setPostSynNeuron(&neuron2);
  neuron1.setPostSynNeuron(&neuron3);


  double inf(100); //in ms
  double sup(400); //in ms
  if ((inf < T_START) or (sup > T_STOP) or (inf > sup)) {
    cerr << "Incorrect values of inf/sup" << endl;
    return 0;
  }
  //We transform these times in terms of steps
  inf /= H;
  sup /= H;

/*****************************************************************************/

  bool spike1(false);
  bool spike2(false);
  bool spike3(false);
  size_t t_stop(T_STOP/H); //in terms of steps

  for (size_t t(0); t < t_stop; ++t) {
    //We update the external current
    if ((t >= inf) and (t <= sup)) {
      neuron1.setIExt(EXT_CURRENT);
    } else {
      neuron1.setIExt(0);
    }

    spike1 = neuron1.update(1);

    //Only neuron1 has post synaptic neurons
    if (spike1) {
      cout << "Spike time : " << neuron1.getSpikeTime()*H << "ms" << endl;

      size_t nbPostSyn_1(neuron1.getPostSynNeuron().size()); //nb of post-syn neurons of neuron1
      for (size_t i(0); i < nbPostSyn_1; ++i) {
        if ((neuron1.getPostSynNeuron())[i] != nullptr) {
            (neuron1.getPostSynNeuron())[i]->receive(D, J);
        }
      }

    }

    spike2 = neuron2.update(1);
    spike3 = neuron3.update(1);

  }



/*****************************************************************************/
void print(string name, Neuron neuron1);

print("membrane_potential_values.txt", neuron1);
print("membrane_potential_values2.txt", neuron2);
print("membrane_potential_values3.txt", neuron3);

/*
//Pour neuron1
    ofstream out;
    out.open("membrane_potential_values.txt");
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

//Pour neuron2
    ofstream out2;
    out2.open("membrane_potential_values2.txt");
    out2.clear();
    if (out2.fail()) {
        cerr << "Erreur lecture fichier" << endl;
    } else {
        vector<double> potential_values2(neuron2.getAllMembranePotentials());
        ostringstream texte2;

        for (unsigned int i(0); i < potential_values2.size(); ++i) {
            texte2 << potential_values2[i] << endl;
        }

     string potentialAsString = texte2.str(); //str() transforms the stream's content into string
     out2 << potentialAsString << endl;
     out2.close();
    }

    //Pour neuron3
        ofstream out3;
        out3.open("membrane_potential_values3.txt");
        out3.clear();
        if (out3.fail()) {
            cerr << "Erreur lecture fichier" << endl;
        } else {
            vector<double> potential_values3(neuron3.getAllMembranePotentials());
            ostringstream texte3;

            for (unsigned int i(0); i < potential_values3.size(); ++i) {
                texte3 << potential_values3[i] << endl;
            }

         string potentialAsString = texte3.str(); //str() transforms the stream's content into string
         out3 << potentialAsString << endl;
         out3.close();
       }*/


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
