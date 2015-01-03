# Python script to plot data from "Surface.h5"

import h5py
import matplotlib.pyplot as plt
import numpy as np

fname = "Surface"

infile = h5py.File(fname + ".h5", 'r')
x = infile["x"]
y = infile["y"]
data = np.array((infile["data"]))
plt.contour(x, y, data.T)
plt.savefig(fname + ".eps")
infile.close()

