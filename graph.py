import numpy as np
import pylab as pl
from collections import Counter

data = np.genfromtxt('spikes_times_neurons.txt')

select= np.array([d for d in data if d[1] < 50])
data1= select.transpose()
pl.scatter(data1[0],data1[1], alpha=0.8, edgecolors='none');
pl.show();

data = data.transpose()
counts = Counter(data[0])
x, y = list(zip(*counts.items()))
print(data[0])
print(counts.most_common(5))
pl.bar(x,y)
pl.show()
