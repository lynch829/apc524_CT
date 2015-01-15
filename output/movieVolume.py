import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
import matplotlib.animation as manimation
import numpy as np
import h5py
import sys

fname = sys.argv[1]
infile = h5py.File(fname, 'r')
x = np.array((infile["x"]))
y = np.array((infile["y"]))
z = np.array((infile["z"]))
data = np.array((infile["data"]))
X, Y = np.meshgrid(x, y)
dmin = data.min()
dmax = data.max()

fig = plt.figure()

def animate(i):
  im = plt.pcolormesh(X, Y, data[i, :, :], vmin = dmin, vmax = dmax)
  plt.title('z = %.2f' % z[i])
  return im

ani = manimation.FuncAnimation(fig, animate, frames = z.shape[0], interval = 50)
# Codec (such as ffmpeg) is needed for saving the animation. 
ani.save(fname[:-3] + ".mp4", fps = 10) 
plt.show()
