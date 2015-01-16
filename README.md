# Developing a Platform for Computed Tomography

##Final Project for APC524 Fall 2014, Princeton University
---------------------------------------------------
### Suerfu, Qi Li, Yao Zhou, Xiang Gao

X-ray computed tomography, or simply CT, is a technique for non-invasive imaging through objects. With appropriate reconstruction algorithm, two/three dimensional cross-sectional images can be obtained from multiple projections along different directions.
This software is capable of simulating such process: generating test objects, forming projections, reconstruction and visualization.

### Description of the Software

- **TEST OBJECT**
Test objects are used to study and check the performance of reconstruction algorithms. The overall base class is called *Image*, from which derives *Curve*(1D), *Surface*(2D), and *Volume*(3D). Each of the derived class must implement *operator(double,double,double,intpl)*, which is used to access values at given points.
Currently test objects are implemented either analytically or numerically. Analytical objects are created by specifying a function rule that determines field values.
Numerical objects are implemented by storing coordinates and corresponding values, and uses Interpolation method to access field values.
If HDF5 is enabled, numerical images can also be read from .h5 files that has the correct format.
If one wants to interface his own test objects, at least *operator()* must be implemented such that line integration is possible.

- **PROJECTION**
Projection is the key process in reconstruction. In CT projection refers to line integrals (of X-ray attenuation coefficient) along a set of parallel lines. Therefore the result of a projection is another function with lower dimension.
*Surface* object has a method *GetProjection(intg,double,...)* that returns a *NumCurve* object as a result of projection along specified direction. The curve object is characterized by the parallel distance to the center.
In calling projection method, an *Integrator* must be specified. This integrator is an abstract class that performs line integrals. Currently implemented integration schemes are: *Trapezoid*, *Parabola*, *Romberg* and *Monte-Carlo*.
Similarly *Volume* has a *GetProjection* method that returns a *NumCurve* at the specified angle and height.
Result of projections are stored in an object called *ImageArray*.

- **RECONSTRUCTION**
Reconstruction refers to combining information from multiple projections to reproduce the scalar field.
  * *ImageArray* object, which stores result of projections has the following features:
  * Store and access *Image* and the angle/height at which they were taken,
  * Call convolution on all the stored *Image* objects with a specified kernal. This kernal is by default Hamming function.
The core of reconstruction is *FilteredBackProjection* class, which takes in an *ImageArray* object, performs convolution and back-project images. The results are superposed and returns a *NumSurface* object.
For more information about reconstruction algorithm, please refer to [*Principles of Computerized Tomographic Imaging*](www.slaney.org/pct/) by Kak and Slaney.
If one wants to interface with our software by implementing different reconstruction algorithm, it is better to work with *ImageArray* objects since they contain essentially all information that is needed for reconstruction.
About usage of classes, please refer to user manual.

- **VISUALIZATION**
All the derived classes of *Image* (*Curve* & *NumCurve*, *Surface* & *NumSurface*, *Volume* & *NumVolume*) are equipped with a method named ExportHDF.
When the method is called, the data in the class is saved into a designated HDF5 file in directory 'output'.
The file includes 1D arrays (/x, /y, & /z, depending on dimension) storing the coordinates of the rectilinear mesh, and array /data storing the value at each node.
To enable this feature, one has to install HDF5, specify HDF5 header and lib locations, and run 'make USE_HDF=1'.
A few sample python scripts can also be found in the output directory to visualize the output data (plotCurve.py, plotSurface.py, & movieVolume.py).
plotCurve.py is used to take in an HDF5 file and produce a 1D function.
plotSurface.py is used to produce png images from a 2D surface.
movieVolume.py will generate a movie that shows cross-section in order from top to bottom. Note that movieVolume.py requires codec (such as FFMpeg) to save the movie.
Example usage: "python plotCurve.py Curve.h5".
Also note that all classes deriving from *Image* have a *Print()* method which prints data points to stdout. User can redirect stdout to a file and use tools of their choice to visualize.
When exporting HDF5 files from 2D and 3D Images, a XDMF file is also generated in the output directory to enable reading and visualizing with VisIt (visit.llnl.gov). In VisIt, simply open the .xmf file with format Xdmf and draw contour, pseudocolor, etc.  
Besides, all the derived classes of Image also have a constructor from reading in data from a HDF5 file that has the same "flavor" as the output file.

### System Requirement

* The software is written in C++. Since lambda function deature is used in performing line integral, to compile C++ compilor that supports C++11 is required.
* Currently this software has been tested on Linux(Ubuntu 12.4) and Mac OS with g++.
* For visualization, HDF5 is required.
* The result can be viewed with either [VisIt](https://wci.llnl.gov/simulation/computer-codes/visit/) or python package [Mayavi] (http://docs.enthought.com/mayavi/mayavi/) which uses VTK. 

### Install and File Description

* To compile:        make
* To enable HDF5:    make USE_HDF=1
* By default:
    - ./include/ contains all header files.
    - ./src/     contains all source files.
    - ./test/    contains functions used to test during development.
    - ./demo/    contains codes for demonstrating usage of this software.
    - ./output/  default location for exporting HDF5 files.
    - ./bin/     binary executable files produced by make.

### Demostration Usage

* demoAna2D: demoAna2D is a demo for 2D Analytical functions to do X-ray simulation and reconstruction. Five analytical functions can be chosen. They are "Batman", Gauss2D, Rectangle, Circle and Triangle. Output is located in the directory ./output/outAna2D.h5.
   * USAGE: ./bin/demoAna2D (number).  number is 0~5 0: Batman, 1: Gauss2D, 2: Circle, 3: Rectangle, 4: Triangle
* demoAna3D: demoAna3D is a demo for 3D analytical functions to do X-ray simulation and reconstruction. Four analytical functions can be chosen. They are Gauss3D, heart, sphere, cube. Output is located in the directory ./output/outAna2D.h5.
   * USAGE: ./bin/demoAna3D (number). number is 0~3 0: Gauss3D, 1: Heart, 2: Sphere, 3: Cube
* demoNum2D: This demo loads a hdf5 file from external sources and output a numerical surface that is the reconstructed image of the origin one. If input from command line is 1, then the default image spine.h5 will be loaded. If input from command line is the path of a hdf5 file specified by the user, then the user-specified file will be loaded. File name of output of this demo is outNum2D.h5. The final image is an image of spine from MATLAB Gallery.
* demoNum3D: This demo loads a hdf5 file from external sources and output a numerical volume that is the reconstructed image of the origin one. If input from command line is 1, then the default image brain.h5 will be loaded. If input from command line is the path of a hdf5 file specified by the user, then the user-specified file will be loaded. File name of output of this demo is outNum3D.h5. The final 3D image is a human brain MRI image from MATLAB Gallery.

### WRITING YOUR OWN CODE

Computing tomography consists of three plus one steps:
1. Creating the geometry/scalar field you want to study.
2. Call GetProjection method on the scalar field you have created, and push the result NumCurves into a, ImageArray.
3. Call FilteredBackProjection() on the ImageArray object which stores projection. This method will return the final 2D/3D reconstructed field.
4. On the reconstructed object, Print() will print the field values to stdout; alternatively one can call ExportHDF to store the reconsrtucted field in a .h5 file.
