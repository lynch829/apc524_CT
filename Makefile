
CXX=g++
CXX_FLAGS=-Wall -g -std=c++0x -I${INC_DIR} -I${SRC_DIR} -lhdf5 -lhdf5_cpp -lhdf5_hl -lhdf5_hl_cpp 

INC_DIR=./include/
SRC_DIR=./src/
TEST_DIR=./test/

.PHONY: test
test : testNumCurve testSBP testNumSurface 

test% : ./test/test%.cpp $(patsubst %.cpp, %.o, $(wildcard ./src/*.cpp))
	${CXX} ${CXX_FLAGS} $^ -o $@
	chmod +x $@

#testSBP : ./test/testSBP.cpp $(patsubst %.cpp, %.o, $(wildcard ./src/*.cpp))
#	${CXX} ${CXX_FLAGS} $^ -o $@
#	chmod +x $@

%.o : %.cpp
	${CXX} ${CXX_FLAGS} -c $< -o $@

${SRC_DIR}%.o : ${SRC_DIR}%.cpp
	${CXX} ${CXX_FLAGS} -c $< -o $@

.PHONY : clean
clean :
	rm ${SRC_DIR}*.o
	rm ${TEST_DIR}*.o
