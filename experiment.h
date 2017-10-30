#ifndef EXPERIMENT_H
#define EXPERIMENT_H

/*!
 * \file experiment.h
 * \brief Experiment class
 * \author emma-roussel
 */

 #include "Constants.hpp"
 #include "network.h"
 #include <fstream>
 using namespace std;

 /*!
  * \class Experiment
  * \brief class allowing to handle a network
  *
  * Create, connect the network and run the experiment.
  *
  */

 class Experiment {
   public :
   //! Constructor
   /*!
    * Builds a network of N neurons with NE excitatory and NI inhibitory neurons.
    * N, NE, NI are constants found in the Constants.hpp file.
    */
   Experiment();

   //! Destructor
   ~Experiment();

   //! Getter for the network
   /*!
    * \return  the network
    */
   Network* getNetwork() const;

   //! Connexion of the network
   /*!
    * Connects the neurons : each neuron will receive C_EXCI excitatory and C_INHI
    * inhibitory connexions from ramdomly chosen neurons.
    * C_EXCI, C_INHI are constants found in the Constants.hpp file.
    */
   void connect();

   //! Runs the experiment
   /*!
    * Updates the network for a time of simulation defined in the Constants.hpp
    * file (T_STOP in ms)
    */
   void run(long simulation_time);

   //! Saves the time spikes and the indexes of neurons which has spiked
   void save_spikes(string file);

   private :
    Network* network;  /*!< network of the experiment */


 };

#endif
