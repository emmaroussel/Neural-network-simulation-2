import numpy as np
import matplotlib.pyplot as pl

data = np.genfromtxt('spikes_times_neurons.txt')

select= np.array([d for d in data if d[0] > 9.999])
data2= select.transpose()
select1= np.array([d for d in select if d[1] < 50])
data1 = select1.transpose()


pl.scatter(data1[0]/0.01,data1[1], alpha=0.8, edgecolors='none', s=1.1, marker="_", color='black');
pl.xlabel('time (ms)')
pl.ylabel('neuron number')
pl.show();



n, bins, patches= pl.hist(data2[0]/0.01, 10000, normed=0, alpha=0.75)
pl.xlabel('time (ms)')
pl.ylim(0, 250)
pl.show()
