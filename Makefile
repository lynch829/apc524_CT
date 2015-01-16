CXX=g++
ifdef USE_HDF
CXX_FLAGS= -DUSE_HDF -Wall -g -std=c++0x
else
CXX_FLAGS=-Wall -g -std=c++0x 
endif
INCLUDE:= -I./include -I/usr/local/hdf5/include -I/usr/local/include
LINKER= -L/usr/local/hdf5/lib -L/usr/local/lib
LIBS= -lhdf5 -lhdf5_cpp -lhdf5_hl -lhdf5_hl_cpp

integrators = ./src/LineIntegral.o ./src/MCIntegrator.o ./src/Parabola.o ./src/Romberg.o ./src/Trapezoid.o

INC_DIR=./include/
SRC_DIR=./src/
TEST_DIR=./test/

all : test demo testIntegration

<<<<<<< HEAD
test : testSBP testNumCurve testNumSurface testVolume testSBP3D test_Intpl test_Intpl2
=======
test : testNumCurve testNumSurface testVolume test_Intpl test_Intpl2 
>>>>>>> f834e64d2f41d6482af9d1d56a3c4b023cc5279a

demo : demoAna2D demoAna3D demoNum2D demoNum3D 

demo% : ./demo/demo%.o $(patsubst %.cpp, %.o, $(wildcard ./src/*.cpp))
	${CXX} ${CXX_FLAGS} ${INCLUDE} $^ ${LINKER} ${LIBS} -o $@
	@chmod +x $@
	@mv $@ ./bin/

test% : ./test/test%.o $(patsubst %.cpp, %.o, $(wildcard ./src/*.cpp))
	${CXX} ${CXX_FLAGS} ${INCLUDE} $^ ${LINKER} ${LIBS} -o $@
	@chmod +x $@
	@mv $@ ./bin/

%.o : %.cpp
	${CXX} ${CXX_FLAGS} ${INCLUDE} -c $< -o $@

testIntegration : ./test/testIntegration.o $(integrators)
	$(CXX) -o $@ $^
	@mv $@ ./bin/

clean :
	@for i in `ls ${SRC_DIR}*.o`; do rm ${i}; done
	@for i in `ls ${TEST_DIR}*.o`; do rm ${i}; done

depend:
	${CXX} -MM ${CXXFLAGS} -I./include ./src/*.cpp > .depend
-include .depend

.PHONY : depend all clean test demo testIntegration
