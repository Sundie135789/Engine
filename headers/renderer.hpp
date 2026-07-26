#pragma once
#include <glm/glm.hpp>
#include "camera.hpp"
#include "dirlight.hpp"
class Gameobject;
class Renderer{
  public:
    void SetCamera(Camera* cam);
    void SetLight(DirectionalLight* light);
    Camera* camera;
    DirectionalLight* light;
    void Submit(Gameobject* gameobject);
    static void NewFrame();
    Renderer();
};
