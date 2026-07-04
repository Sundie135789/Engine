#pragma once
#include "gameobject.hpp"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "imgui.h"
class UI{
  public:
  static void LoadInspector();
  static void BeginFrame();
  static void EndFrame();
  static void Init(GLFWwindow* window);
  static void Menubar();
  static void Hierarchy();
};



