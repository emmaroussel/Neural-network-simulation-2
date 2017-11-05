<<<<<<< HEAD
	This project allows to simulate a recurrent spiking network of neurons as described in Brunel, NJ. Computational Neuroscience 2000. The aim is to mimic a network of 12500 neurons with 10000 excitatory neurons and 2500 inhibitory ones. In this model, we assume each neuron is targeted by C_EXCI(=1000) connexions from excitatory neurons, C_INHI(=250) connexions from inhibitory neurons and C_EXT(=1000) connexions from excitatory neurons outside the network. Note that a neuron can have connexion(s) with itself, and can have multiple connexions with the same neuron.
	When a neuron exceeds the firing threshold, it spikes. As a consequence, it will transmit to its post-synaptic neurons a signal which has a different value depending on the weight of the connexion (which changes if the spiking neuron is excitatory or inhibitory). These post-synaptic neurons will receive it after a certain delay. The default constants allow to simulate a network with stationary global activity and irregularly firing neurons.

Several simulation cases of simulation are possible :

1) You want to create a network with 12500(=N) neurons :
- Create an Experiment.
- Connect the network in it with the connect method of Experiment. (A message will appear on the terminal when the connection is done).
- Run your experiment with the run method of Experiment -> you have to specify your simulation time (in ms) when calling this method.
You can store the spike times and the corresponding neurons which have spiked with the save method of Experiment.

2) You want to create a network with a few neurons (for example in a test function) :
- Create manually your neurons, and build a vector with pointers of these neurons.
- Create a network by calling the constructor of network using a list of pointers.
- Create connexions between neurons manually by using the method of Network : addConnexion
You can then update your network.

=======
This project allows to simulate a network of neurons, several cases are possible : 

1) You want to create a network with a few neurons : 
Create manually your neurons, and build a vector with pointers of these neurons.
Create a network by calling the constructor of network using a list of pointers.
Create connexions between neurons manually by using the method of Network : addConnexion
You can then update your network.

2) You want to create a network with 12500(=N) neurons : 
Create an Experiment.
Connect the network in it with the connect method of Experiment. (A message will appear on the terminal when the connection is done).
Run your experiment with the run method of Experiment -> you have to specify your simulation time (in ms) when calling this method.
You can store the spike times and the corresponding neurons which have spiked with the save method of Experiment.

>>>>>>> 6c191c032fdcfd2317cff70767da18ca6111a8da

-> You can modify the number of neurons (N) in the Constants.hpp file which gathers a lot of other constants.
-> Total number of ms will appear on the terminal at the end of the execution.


<<<<<<< HEAD
Remarks :

- if you do the option 1), for a simulation time of 1sec(=1000ms) the execution time will approximately be between 70sec and 90sec (when running on the IC Virtual Machine), and between 85 and 155sec on the SV Virtual Machine.
- when executing test_neuron.cpp, the last tests corresponding to NetworkTest take a few seconds to run since we connect the network via an experiment.
- in the main_neuron.cpp : a print method is available to print all the membrane potential values of a specific neuron.
- the spike times and the corresponding neuron(s) which has spiked are available in a file (spikes_and_neurons_values.txt) (which is in the build folder) if you used the save method of Experiment.


Compilation and execution :

Use CMake to compile : in the folder containing the .h and .cpp files, create a build folder (if a build file is already there, delete it and create an empty one), go to this folder, then enter « cmake .. » then « make ».
To execute, enter in the command line : ./neuron

Documentation :

When entering the make command, it will automatically generate the Doxygen documentation which will be available in the doc file.


Test with GoogleTest :

You can test the program with GoogleTest by entering : ./unittest after compiling.


Generate plots :

- The graphs can be generate thanks to a python code (graphs.py) based on the spikes_and_neurons_values.txt. (see graph folder). The histogramme (instantaneous firing frequency) produced, is similar to the one of Brunel’s paper since the bins used are of 0.1ms.
Warning : python does not work on the Virtual Machine… I joined in the graphs folder the python files, the scatter plot and histogramme produced for each of plots of Figure8 of Brunei’s paper. The results are quiet similar as the ones expected (especially for the scatter plots).
Remark : I used files which correspond to a simulation of 1200ms since in Brunel’s paper we want to analyze the period of time between 1000 and 1200ms (for all cases except A where it is between 500 and 600ms))
I joined the spikes_times_neurons.txt files in cases B,C and D (where I only copied the values from the period of time considered).

To test with different values of constants, go to the Constants.hpp file and change these values, re compile your file with make, and then execute your program.
In the graphs folder, we can find the plots for the following cases : 
- Case A : g = 3, eta = 2 ; almost fully synchronized network, neurons firing regularly at high rates.
- Case B : g = 6, eta = 4 ; fast oscillation of the global activity, neurons firing irregularly at a rate that is lower than the global frequency.
- Case C : g = 5, eta = 2 ; Stationary global activity, irregularly firing neurons.
- Case D : g = 0.9, eta = 4.5 ; slow oscillation of the global activity, neurons firing irregularly at very low rates. 

Comparisons between firing rate obtained and theoretical ones (see Brunel’s paper page 196)
(Case A : obtained = 376Hz) 
Case B : expected = 55.8Hz, obtained = 58Hz
Case C : expected = 38Hz, obtained = 39Hz
Case D : expected = 6.5Hz, obtained = 6Hz
(The obtained values were taken from the value displayed on the terminal at the end of the execution for each case)

- Another way to generate the plots is to use the website : https://cs116-plot.antoinealb.net/
where we just have to upload your .txt file (which is already in the correct form : in the first column 1 represents 100ms as required to produce plots with correct units with this site). However, with this method the histogramme will not be as the one of Brunel’s paper since bins of 20ms were used. 
=======
Remarks : 

- if you do the option 2), for a simulation time of 1sec(=1000ms) the execution time will be around 1min10sec (when running on the IC Virtual Machine), and around 110sec on the SV Virtual Machine.
- when executing test_neuron.cpp, the last tests corresponding to NetworkTest take a few seconds to run since we connect the network via an experiment.
- in the main_neuron.cpp : a print method is available to print all the membrane potential values of a specific neuron. 
- the spike times and the corresponding neuron(s) which has spiked are available in a file (spikes_and_neurons_values.txt) (which is in the build folder) if you used the save method of experiment.


Compilation and execution : 

Use CMake to compile : in the folder containing the .h and .cpp files, create a build folder, go to this folder, then enter « cmake .. » then « make ».
When entering the make command, it will automatically generate the Doxygen documentation which will be available in the doc file. 


Generate plots : 

The graphs can be generate thanks to a python code (graphs.py) based on the spikes_and_neurons_values.txt. (see graph_python folder). The histogramme (instantaneous firing frequency) produced is similar to the one of Brunel’s paper (since the bins used are of 0.1ms). 
Warning : python does not work on the Virtual Machine.. I joined in the graph_python folder the python file, the scatter plot and histogramme produced with the spikes_and_neurons_values.txt also in this folder (which was computed wight g=5 and (nu_ext/nu_thrs)=2)
Another way to generate the plots is the use the website : https://cs116-plot.antoinealb.net/
where we just have to upload your .txt file (which is in the correct form : in the first column 1 represents 100ms as required to produce plots with correct units with this site). However, with this method the histogramme will not be as the one of Brunel’s paper since bins of 20ms were used.

If you want to test with different values of constants (ex : change g or eta constants), go to the Constants.hpp file and change these values, re compile your file with make, and then execute your program.
//(Some .txt files are available for specific values of g and eta in the graph folder.) 


Test with GoogleTest : 

You can test the program with GoogleTest by entering : ./unittest after compiling with make.


>>>>>>> 6c191c032fdcfd2317cff70767da18ca6111a8da


