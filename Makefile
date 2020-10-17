COMMON_DIR = Common/src/

CXX = /usr/bin/g++
CXXFLAGS = -std=c++17 -flto -O3 -I${COMMON_DIR} -Wall -g

LIBS = -lGL -lglut -lGLEW -lIL -lILU -lSDL2

COMMON_OBJECTS = framebuffer.o quad.o shader.o texture.o cube.o camera.o app.o vao.o
LAB_OBJECTS = main.o

EXEC_NAME = mri_d

lab3: ${COMMON_OBJECTS} ${LAB_OBJECTS}
	${CXX} ${CXXFLAGS} -o ${EXEC_NAME} ${COMMON_OBJECTS} ${LAB_OBJECTS} ${LIBS}

main.o: main.cpp
	${CXX} ${CXXFLAGS} -c -o main.o main.cpp

app.o: app.cpp app.hpp
	${CXX} ${CXXFLAGS} -c -o app.o app.cpp

clean:
	rm -f *.o
	rm -f ${EXEC_NAME}

include ${COMMON_DIR}common.mk
