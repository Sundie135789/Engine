CXX = g++
CXXFLAGS = -g -Ivendor/imgui -Ivendor/imgui/backends -std=c++17
 
SRC = main.cpp shader.cpp loadshader.cpp mesh.cpp texture.cpp transform.cpp gameobject.cpp renderer.cpp material.cpp ui.cpp camera.cpp dirlight.cpp window.cpp
OBJ = $(SRC:.cpp=.o)

IMGUI_SRC = \
vendor/imgui/imgui.cpp \
vendor/imgui/imgui_draw.cpp \
vendor/imgui/imgui_tables.cpp \
vendor/imgui/imgui_widgets.cpp \
vendor/imgui/backends/imgui_impl_glfw.cpp \
vendor/imgui/backends/imgui_impl_opengl3.cpp

IMGUI_OBJ = $(IMGUI_SRC:.cpp=.o)

all: main

main: $(OBJ) $(IMGUI_OBJ)
	$(CXX) $(OBJ) $(IMGUI_OBJ) -o main -lGLEW -lGL -lglfw

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(IMGUI_OBJ) main
