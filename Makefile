CSTD=c++14
CC=clang++
INCLUDE_PATHS=-I/usr/local/include -I/opt/X11/include
LIBRARY_PATHS=-L/usr/local/lib -I/opt/X11/lib
COMPILER_PLAGS=-Wall
LINKER_FLAGS=-framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -lglfw3 -lglew
OBJS=src/main/*.cpp
OBJ_NAME=build/opengl-test

clean:
	rm -rf build

shaders:
	mkdir -p build/assets/shaders && \
	cp src/shader/* build/assets/shaders/

osx: $(OBJS) src/opengl/*.cpp shaders
	if [ ! -d 'build' ]; then mkdir build; fi; \
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -std=$(CSTD) -o $(OBJ_NAME)