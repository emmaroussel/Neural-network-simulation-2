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


-> You can modify the number of neurons (N) in the Constants.hpp file which gathers a lot of other constants.
-> Total number of ms will appear on the terminal at the end of the execution.


Remarks : 
- if you do the option 2), for a simulation time of 1sec(=1000ms) the execution time will be around 1min10sec (when running on the IC Virtual Machine), and around 110sec on the SV Virtual Machine.
- when executing test_neuron.cpp, the last tests corresponding to NetworkTest take a few seconds to run since we connect the network via an experiment.
- in the main_neuron.cpp : a print method is available to print all the membrane potential values of a specific neuron. 
- the spike times and the corresponding neuron(s) which has spiked are available in a file (spikes_and_neurons_values.txt) (which is in the build folder) if you used the save method of experiment.

Use CMake to compile : in the folder containing the .h and .cpp files, create a build folder, go to this folder, then enter « cmake .. » then « make ».
When entering the make command, it will automatically generate the Doxygen documentation which will be available in the doc file. 

The graphs can be generate thanks to a python code (graphs.py) based on the spikes_and_neurons_values.txt.
If you want to test with different values for the constant (ex : change g or eta constants), go to the Constants.hpp file and change the values, re -compile your file with make, and then execute your program.
(Some .txt files are available for specific values of g and eta in the graph folder.) 

You can test the program with GoogleTest by entering : ./unittest after compiling with make.




