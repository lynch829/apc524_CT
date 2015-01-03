CXX=g++
CXX_FLAGS=-Wall -g -std=c++0x 
INCLUDE= -I./include -I/usr/local/hdf5/include -I/usr/local/include
LINKER= -L /usr/local/hdf5/lib
LIBS= -lhdf5 -lhdf5_cpp -lhdf5_hl -lhdf5_hl_cpp

INC_DIR=./include/
SRC_DIR=./src/
TEST_DIR=./test/

.PHONY: test
test : testNumCurve testSBP testNumSurface testVolume

test% : ./test/test%.o $(patsubst %.cpp, %.o, $(wildcard ./src/*.cpp))
	${CXX} ${CXX_FLAGS} ${INCLUDE} $^ ${LINKER} ${LIBS} -o $@
	@chmod +x $@
	@mv $@ ./bin/

%.o : %.cpp
	${CXX} ${CXX_FLAGS} ${INCLUDE} -c $< -o $@

#${SRC_DIR}%.o : ${SRC_DIR}%.cpp
#	${CXX} ${CXX_FLAGS} ${INCLUDE} -c $< -o $@

.PHONY : clean
clean :
	@for i in `ls ${SRC_DIR}*.o`; do rm ${i}; done
	@for i in `ls ${TEST_DIR}*.o`; do rm ${i}; done
