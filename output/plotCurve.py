# Python script to plot data from "Curve.h5"

import h5py
import matplotlib.pyplot as plt

fname = "Curve"

infile = h5py.File(fname + ".h5", 'r')
x = infile["x"]
data = infile["data"]
plt.plot(x, data)
plt.savefig(fname + ".eps")
infile.close()

