CXX = ccache clang++
CXXFLAGS = -std=c++20 -Wall -O2 -Iheaders
LIBS = -lGL -lGLEW -lglfw

SRC = main.cpp shader.cpp mesh.cpp gameobject.cpp camera.cpp transform.cpp sidepane.cpp readshader.cpp texture.cpp text.cpp character.cpp
OBJ = $(SRC:.cpp=.o)

engine: $(OBJ)
	$(CXX) $(OBJ) $(LIBS) -o engine

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o engine
