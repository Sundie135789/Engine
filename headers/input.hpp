#pragma once
#include "window.hpp"
#include "camera.hpp"
#include "../vendor/imgui/imgui.h"
class Input{
  public:
    static void HandleEngineInput(Window* window, Camera* editorCamera, float deltaTime, float& lastX, float& lastY, bool& lastMouse);
    static void HandleGameInput(Window* window, Camera* camera, float deltaTime, float& lastX, float& lastY, bool & lastMouse);
    static double mouseX;
    static double mouseY;
    static void WASDMouse(bool& firstMouse, float &lastX, float& lastY, Camera* gameCamera, Window* window, float deltaTime);
    struct Keybind{
      std::string actionName;
      char assignedKey;
      bool waitingForInput = false;
    };
    static std::vector<Keybind>* gameKeybinds;
    static void PopulateKeybinds();
};
