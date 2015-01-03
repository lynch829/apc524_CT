# Python script to plot data from "Surface.h5"
# /usr/bin/env python

import h5py
import matplotlib.pyplot as plt
import numpy as np
import sys

fname = sys.argv[1]

infile = h5py.File(fname, 'r')
x = infile["x"]
y = infile["y"]
data = np.array((infile["data"]))
plt.contour(x, y, data.T)
plt.savefig(fname + ".eps")
infile.close()

