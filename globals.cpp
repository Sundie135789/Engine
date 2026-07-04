#include "headers/globals.hpp"

std::unique_ptr<Window> mainWindow = std::make_unique<Window>(2560, 1920, "Game Engine - x64");
std::vector<Gameobject*> gameobjects;
Camera* editorCamera = new Camera();
Camera* gameCamera = new Camera();
float lastX, lastY;
bool firstMouse = true;
bool gameObjectSelected = true;
EngineState g_EngineState = EngineState::Editing;
int untitled_number = 0;
int selected = -1;
