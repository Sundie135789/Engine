#pragma once

#include "camera.hpp"
#include "window.hpp"
#include <memory>
#include "gameobject.hpp"
#include "dirlight.hpp"
extern std::unique_ptr<Window> mainWindow;
extern std::vector<std::unique_ptr<Gameobject>> gameobjects;
extern int selected;
extern Camera* editorCamera, *gameCamera;
extern float lastX, lastY;
extern bool firstMouse, gameObjectSelected;
extern float camera_speed;
extern float sensitivity;
enum class EngineState{
  Playing,
  Editing
};
extern EngineState g_EngineState;
extern int cube_untitled_number;
extern int plane_untitled_number;
extern std::vector<std::string> textures; 
extern bool vsync;
extern DirectionalLight* mainDirLight;
extern std::vector<Texture*> g_loadedTextures;
