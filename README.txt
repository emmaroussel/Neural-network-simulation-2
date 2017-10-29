This project allows to simulate a network of neurons, several cases are possible : 
1) You want to create a network with a few neurons : 
Create manually your neurons, and build a vector with pointers of these neurons.
Create a network by calling the constructor of network using a list of pointers.
Create connexions between neurons manually by using the method of Network : addConnexion
You can then update your network.

2) You want to create a network with 12500 neurons : 
Create a network with the constructor by default.
You can then update your network.
-> You can modify this number of neurons in the Constants.hpp file which gathers a lot of other constants (for example the time of simulation).
-> When the network is built a message will appear on the terminal followed by the number of ms it took to build the network.
-> When the network is updated a message will appear on the terminal followed by the number of ms it took to update the network.
-> Total number of ms will appear on the terminal at the end of the execution.


Remarks : 
- if you do the option 2), the execution time is long because at each time step you have to update every single neuron.
For example, for a simulation of 50ms for the network, the execution time will be around 129000ms ≈ 2min15sec. 
- when executing test_neuron.cpp, the last tests corresponding to NetworkTest take a few seconds to run for the same reason.
- in the main_neuron.cpp : a print method is available to print all the membrane potential values of a specific neuron. 
- the spike times and the corresponding neuron(s) which has spiked are available in a file (spikes_and_neurons_values.txt)



