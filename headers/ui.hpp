#pragma once
#include "gameobject.hpp"
#include <GLFW/glfw3.h>
class UI{
  public:
  static void LoadInspector(Gameobject* gameobject);
  static void BeginFrame();
  static void EndFrame();
  static void Init(GLFWwindow* window);
};


