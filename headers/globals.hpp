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
enum class EngineState{
  Playing,
  Editing
};
extern EngineState g_EngineState;
extern int cube_untitled_number;
extern int plane_untitled_number;
extern std::vector<std::string> textures; 
extern DirectionalLight* mainDirLight;
extern std::vector<Texture*> g_loadedTextures;
extern unsigned int framebuffer;
extern unsigned int quadVAO;
extern unsigned int textureColorBuffer;
struct GraphicsSettings{
  bool chromaticAbberation = false;
  float chromaticAbberationStrength = 0.05f;
  bool vsync = true;
};
struct ControlSettings{
  float camera_speed = 5.0f;
  float sensitivity = 0.1f;
};
struct Settings {
  GraphicsSettings graphics;
  ControlSettings controls;
};

extern Settings settings;
extern Shader* fboShader;
extern int model_untitled_number;
//extern std::vector<std::string> logs;
