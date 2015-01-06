# after data is loaded from plotVolume, plot the contour surface.
# usage: python -- execfile("plotMaya.py")
#x, y, z = np.ogrid[-10:10:20j, -10:10:20j, -10:10:20j]
#s = np.sin(x*y*z)/(x*y*z)
from mayavi import mlab
src = mlab.pipeline.scalar_field(data)
mlab.pipeline.iso_surface(src, contours=[data.min()+0.1*data.ptp(), ], opacity=0.3)
mlab.pipeline.iso_surface(src, contours=[data.max()-0.1*data.ptp(), ],)
mlab.show()
