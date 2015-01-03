# Python script to plot data from 
# /usr/bin/env python

import h5py
import matplotlib.pyplot as plt
import numpy as np
import sys

fname = sys.argv[1]

infile = h5py.File(fname + ".h5", 'r')
x = infile["x"]
y = infile["y"]
x = np.array((infile["x"]))
y = np.array((infile["y"]))
data = np.array((infile["data"]))
X, Y = np.meshgrid(x, y)
plt.pcolormesh(X, Y, data.T)
plt.savefig(fname + ".png")
infile.close()

