#!/bin/bash
export GLFW_PLATFORM=x11
g++ main.cpp mesh.cpp readshader.cpp shader.cpp gameobject.cpp camera.cpp transform.cpp -o main -lglfw -lGLEW -lGL && ./main 
