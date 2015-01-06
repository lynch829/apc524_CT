# load the h5py and data.
# execute this file with python -- execfile("plotVolume.py")
import numpy as np
import h5py
#import sys

fname = "test.h5" #sys.argv[1]
infile = h5py.File(fname, 'r')
x = np.array((infile["x"]))
y = np.array((infile["y"]))
z = np.array((infile["z"]))
data = np.array((infile["data"]))
dmin = data.min()
dmax = data.max()

#x, y, z = np.ogrid[-10:10:20j, -10:10:20j, -10:10:20j]
#s = np.sin(x*y*z)/(x*y*z)
#from mayavi import mlab
#src = mlab.pipeline.scalar_field(data)
#mlab.pipeline.iso_surface(src, contours=[data.min()+0.1*data.ptp(), ], opacity=0.3)
#mlab.pipeline.iso_surface(src, contours=[data.max()-0.1*data.ptp(), ],)
#mlab.show()
