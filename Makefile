CC=clang++
CSTD=c++14

UNIX_INCLUDE_PATHS=-I/usr/local/include -I/opt/X11/include
UNIX_LIBRARY_PATHS=-L/usr/local/lib -I/opt/X11/lib

COMPILER_PLAGS=-Wall

LINKER_FLAGS=-lglfw3 -lglew
OSX_LINKER_FLAGS=-framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo

OBJS=src/main/*.cpp
OPENGL_OBJS=src/opengl/*.cpp
OBJ_NAME=build/opengl-test

clean:
	rm -rf build

shaders:
	mkdir -p build/assets/shaders && \
	cp src/shader/* build/assets/shaders/

osx: $(OBJS) $(OPENGL_OBJS) shaders
	if [ ! -d 'build' ]; then mkdir build; fi; \
	$(CC) $(OBJS) $(OPENGL_OBJS) $(UNIX_INCLUDE_PATHS) $(UNIX_LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(OSX_LINKER_FLAGS) -std=$(CSTD) -o $(OBJ_NAME)