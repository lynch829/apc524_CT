# Makefile for CT reconstruction software, APC524.

# compiled with g++
CXX = g++

# C++11 required. Debugging enabled.
CXX_FLAGS = -Wall -g -std=c++0x 

# INCLUDE must include hdf5 header files.
INCLUDE = -I./include 

# if USE_HDF is defined, pass it to enable HDF5 in compiling, and add HDF headers and libs to variable.
# user is responsible for changing the line below to point to his/her installation of HDF5
ifdef USE_HDF
CXX_FLAGS += -DUSE_HDF
# include HDF headers
INCLUDE += -I/usr/local/hdf5/include -I/usr/local/include
# specify where to look for HDF libraries
LINKER = -L/usr/local/hdf5/lib -L/usr/local/lib
# specify which library to link to
LIBS = -lhdf5 -lhdf5_cpp -lhdf5_hl -lhdf5_hl_cpp
endif

# geometry
GEOM = ./src/Image.o ./src/Curve.o ./src/Surface.o ./src/Volume.o
# required for reconstruction
RECN = ./src/FilteredBackProjection.o ./src/NumCurve.o ./src/NumSurface.o ./src/NumVolume.o ./src/ImageArray.o ./src/globals.o ./src/LineIntegral.o ./src/Trapezoid.o ./src/Interpolator.o ./src/Bilinear.o


all : test demo

test : testNumCurve testNumSurface testVolume test_Intpl testIntegration testInterpolation

demo : demoAna2D demoAna3D demoNum2D demoNum3D 

demoAna2D : ./demo/demoAna2D.o ./src/TestFunctions.o ./src/AnaImage.o ${RECN} ${GEOM}
	@${CXX} ${CXX_FLAGS} ${INCLUDE} $^ ${LINKER} ${LIBS} -o $@
	@mv $@ ./bin/

demoAna3D : ./demo/demoAna3D.o ./src/TestFunctions.o ./src/AnaImage.o ${RECN} ${GEOM}
	@${CXX} ${CXX_FLAGS} ${INCLUDE} $^ ${LINKER} ${LIBS} -o $@
	@mv $@ ./bin/

demoNum2D : ./demo/demoNum2D.o ${RECN} ${GEOM}
	@${CXX} ${CXX_FLAGS} ${INCLUDE} $^ ${LINKER} ${LIBS} -o $@
	@mv $@ ./bin/

demoNum3D : ./demo/demoNum3D.o ${RECN} ${GEOM}
	@${CXX} ${CXX_FLAGS} ${INCLUDE} $^ ${LINKER} ${LIBS} -o $@
	@mv $@ ./bin/

testNumCurve : ./test/testNumCurve.o ${RECN} ${GEOM} ./src/TestFunctions.o
	@${CXX} ${CXX_FLAGS} ${INCLUDE} $^ ${LINKER} ${LIBS} -o $@
	@mv $@ ./bin/

testNumSurface : ./test/testNumSurface.o ${RECN} ${GEOM} ./src/AnaImage.o ./src/TestFunctions.o
	@${CXX} ${CXX_FLAGS} ${INCLUDE} $^ ${LINKER} ${LIBS} -o $@
	@mv $@ ./bin/

testVolume : ./test/testVolume.o ${RECN} ${GEOM} ./src/AnaImage.o ./src/TestFunctions.o
	@${CXX} ${CXX_FLAGS} ${INCLUDE} $^ ${LINKER} ${LIBS} -o $@
	@mv $@ ./bin/

test_Intpl : ./test/test_Intpl.o ${RECN} ${GEOM} ./src/AnaImage.o
	@${CXX} ${CXX_FLAGS} ${INCLUDE} $^ ${LINKER} ${LIBS} -o $@
	@mv $@ ./bin/

testIntegration : ./test/testIntegration.o ./src/LineIntegral.o ./src/Parabola.o ./src/Romberg.o ./src/Trapezoid.o ./src/MCIntegrator.o
	@$(CXX) -o $@ $^
	@mv $@ ./bin/

testInterpolation : ./test/testInterpolation.o ./src/globals.o 
	@${CXX} ${CXX_FLAGS} ${INCLUDE} $^ ${LINKER} ${LIBS} -o $@
	@mv $@ ./bin/

%.o : %.cpp
	${CXX} ${CXX_FLAGS} ${INCLUDE} -c $< -o $@

.PHONY : clean
clean :
	-@rm -f ./src/*.o > /dev/null 2>&1
	-@rm -f ./test/*.o > /dev/null 2>&1
	-@rm -f .depend > /dev/null 2>&1

.PHONY : depend
depend:
	${CXX} -MM ${CXXFLAGS} -I./include ./src/*.cpp > .depend
-include .depend

