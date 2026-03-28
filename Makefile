# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -I./headers -I./assets 
LDFLAGS = -lglfw -lGLEW -lGL -lm -lassimp

# Source files
SOURCES = material.cpp gameobject.cpp main.cpp camera.cpp lang.cpp mesh.cpp readfile.cpp shader.cpp texture.cpp transform.cpp import.cpp 
IMGUI_SOURCES = assets/imgui.cpp assets/imgui_draw.cpp assets/imgui_widgets.cpp assets/imgui_tables.cpp assets/imgui_stdlib.cpp assets/imgui_demo.cpp assets/imgui_impl_glfw.cpp assets/imgui_impl_opengl3.cpp 

# Object files
OBJECTS = $(SOURCES:.cpp=.o)
IMGUI_OBJECTS = $(IMGUI_SOURCES:.cpp=.o)
ALL_OBJECTS = $(OBJECTS) $(IMGUI_OBJECTS)

# Output executable
TARGET = engine

# Default target
all: $(TARGET)

# Link executable
$(TARGET): $(ALL_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Compile .cpp to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean
clean:
	rm -f $(ALL_OBJECTS) $(TARGET)

# Rebuild
rebuild: clean all

# Run
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean rebuild run
