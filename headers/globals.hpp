#pragma once

#include "camera.hpp"
#include "window.hpp"
#include <memory>
#include "gameobject.hpp"
extern std::unique_ptr<Window> mainWindow;
extern std::vector<Gameobject*> gameobjects;
extern Camera* editorCamera, *gameCamera;
extern float lastX, lastY;
extern bool firstMouse, gameObjectSelected;

enum class EngineState{
  Playing,
  Editing
};
extern EngineState g_EngineState;
