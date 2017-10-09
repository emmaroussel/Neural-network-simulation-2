#include "neuron2.h"
#include <fstream>
#include <sstream>

int main() {
  Neuron neuron1;
  Neuron neuron2;
  neuron1.setPostSynNeuron(&neuron2);

  void TEST(double t_spike, Neuron n2);

  double inf(100); //in ms
  double sup(400); //in ms
  if ((inf < T_START) or (sup > T_STOP) or (inf > sup)) {
    cerr << "Incorrect values of inf/sup" << endl;
    return 0;
  }
  //We transform these times in terms of steps
  inf /= H;
  sup /= H;


  bool spike1(false);
  bool spike2(false);
  size_t t_stop(T_STOP/H); //in terms of steps

  //FOR TEST
  double time(0);
  bool hasSpiked(false);
  bool delay_passed(false);

  for (size_t t(0); t < t_stop; ++t) {
    //We update the external current
    if ((t >= inf) and (t < sup)) {
      neuron1.setIExt(EXT_CURRENT);
    } else {
      neuron1.setIExt(0);
    }

    //we update the neurons for one step of time
    spike1 = neuron1.update(1);

    if (spike1) {
      cout << "Spike time : " << neuron1.getSpikeTime()*H << "ms" << endl;

      if (neuron1.getPostSynNeuron() != nullptr) {
          neuron1.getPostSynNeuron()->receive(D, J);
      }

      //FOR TEST
      time = 0;
      hasSpiked = true;
    }

    spike2 = neuron2.update(1);


    //TEST
    ++time;
    if ((hasSpiked)&&(time > D)) {
      TEST(neuron1.getSpikeTime(), neuron2);
      hasSpiked = false;
    }


  }

/*****************************************************************************/

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


  return 0;
}


void TEST(double t_spike, Neuron n2) {
  //t_spike corresponds to a time spike of neuron1
  //Membrane potentials of n2 before and after neuron1 spiked
  double v_bef_spike((n2.getAllMembranePotentials())[t_spike - 1]);
  double v_af_spike((n2.getAllMembranePotentials())[t_spike + D]);

  cout << "Membrane potential before neuron1 spiked : "
       << v_bef_spike
       << endl;

  cout << "Membrane potential after neuron1 spiked and delay is passed : "
       << v_af_spike
       << endl;

  if (abs((v_af_spike - v_bef_spike)- J) < EPSILON)  {
    cout << "TEST PASSED" << endl;
  } else {
    cout << "TEST FAILED" << endl;
  }
}
