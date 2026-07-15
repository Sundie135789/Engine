#include "headers/globals.hpp"
#include "headers/dirlight.hpp"

std::unique_ptr<Window> mainWindow = std::make_unique<Window>(2560, 1920, "Game Engine - x64");
std::vector<std::unique_ptr<Gameobject>> gameobjects;
Camera* editorCamera = new Camera();
Camera* gameCamera = new Camera();
float lastX, lastY;
bool firstMouse = true;
bool gameObjectSelected = true;
EngineState g_EngineState = EngineState::Editing;
int selected = -1;
int cube_untitled_number = 0;
int plane_untitled_number = 0;
bool vsync = true;
DirectionalLight* mainDirLight = new DirectionalLight(glm::vec3(-0.5f, -1.0f, -0.8f), glm::vec3(1.0f, 1.0f, 1.0f));
//DirectionalLight* mainDirLight = nullptr;
std::vector<Texture*> g_loadedTextures;
float camera_speed = 10.0f;
float sensitivity = 0.1f;
