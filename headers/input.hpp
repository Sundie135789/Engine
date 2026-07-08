#pragma once
#include "window.hpp"
#include "camera.hpp"
class Input{
  public:
    static void HandleEngineInput(Window* window, Camera* editorCamera, float deltaTime, float& lastX, float& lastY, bool& lastMouse);
    static void HandleGameInput(Window* window, Camera* camera);
    static double mouseX;
    static double mouseY;
};
