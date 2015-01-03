
CXX=g++
CXX_FLAGS=-Wall -g -std=c++0x -I${INC_DIR} -I${SRC_DIR}

INC_DIR=./include/
SRC_DIR=./src/
TEST_DIR=./test/

test_sbp : ./test/test_sbp.cpp $(patsubst %.cpp, %.o, $(wildcard ./src/*.cpp))
	${CXX} ${CXX_FLAGS} $^ -o $@
	chmod +x $@

test_anaimage : ./test/test_anaimage.cpp $(patsubst %.cpp, %.o, $(wildcard ./src/*.cpp))
	${CXX} ${CXX_FLAGS} $^ -o $@
	chmod +x $@
test_volume : ./test/test_volume.cpp $(patsubst %.cpp, %.o, $(wildcard ./src/*.cpp))
	${CXX} ${CXX_FLAGS} $^ -o $@
	chmod +x $@
%.o : %.cpp
	${CXX} ${CXX_FLAGS} -c $< -o $@

${SRC_DIR}%.o : ${SRC_DIR}%.cpp
	${CXX} ${CXX_FLAGS} -c $< -o $@

.PHONY : clean
clean :
	rm ${SRC_DIR}*.o
	rm ${TEST_DIR}*.o
