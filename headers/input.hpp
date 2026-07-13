#pragma once
#include "window.hpp"
#include "camera.hpp"
class Input{
  public:
    static void HandleEngineInput(Window* window, Camera* editorCamera, float deltaTime, float& lastX, float& lastY, bool& lastMouse);
    static void HandleGameInput(Window* window, Camera* camera, float deltaTime, float& lastX, float& lastY, bool & lastMouse);
    static double mouseX;
    static double mouseY;
    static bool standardWASDMouse;
    static void WASDMouse(bool& firstMouse, float &lastX, float& lastY, Camera* gameCamera, Window* window, float deltaTime);
};
