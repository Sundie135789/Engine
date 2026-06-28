#pragma once
#define SENSITIVITY 0.1f
#define ENGINE_CAMERA_SPEED 10.0f
#include "window.hpp"
#include "camera.hpp"
class Input{
  public:
    static void HandleEngineInput(Window* window, Camera* editorCamera, float deltaTime, float lastX, float lastY, bool lastMouse);
    static void HandleGameInput();
    static double mouseX;
    static double mouseY;
};
