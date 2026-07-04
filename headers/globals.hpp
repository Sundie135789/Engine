#pragma once

#include "camera.hpp"
#include "window.hpp"
#include <memory>
#include "gameobject.hpp"
extern std::unique_ptr<Window> mainWindow;
extern std::vector<Gameobject*> gameobjects;
extern int selected;
extern Camera* editorCamera, *gameCamera;
extern float lastX, lastY;
extern bool firstMouse, gameObjectSelected;
extern int untitled_number;
enum class EngineState{
  Playing,
  Editing
};
extern EngineState g_EngineState;
