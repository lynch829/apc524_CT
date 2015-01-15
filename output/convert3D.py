import scipy.io
import sys
import h5py
import numpy as np

infile = sys.argv[1]

data = scipy.io.loadmat(infile)
N = data[infile[:-4]].T.shape
outfile = h5py.File(infile[:-4] + ".h5", 'w')

dset = outfile.create_dataset("/data", N, dtype='f')
dset[...] = data[infile[:-4]].T

x = outfile.create_dataset("/x", (N[2],), dtype='f')
x.attrs['size of x'] = N[2]
x[...] = np.arange(N[2])/float(N[2]-1) - .5

y = outfile.create_dataset("/y", (N[1],), dtype='f')
y.attrs['size of y'] = N[1]
y[...] = np.arange(N[1])/float(N[1]-1) - .5

z = outfile.create_dataset("/z", (N[0],), dtype='f')
z.attrs['size of z'] = N[0]
z[...] = np.arange(N[0])/float(N[0]-1) - .5
