# Python script to plot data from 
# /usr/bin/env python

import h5py
import matplotlib.pyplot as plt
import sys

fname = sys.argv[1]

infile = h5py.File(fname + ".h5", 'r')
x = infile["x"]
data = infile["data"]
plt.plot(x, data)
plt.savefig(fname + ".png")
infile.close()

