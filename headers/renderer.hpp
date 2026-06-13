#pragma once
#include <glm/glm.hpp>
#include "camera.hpp"
class Gameobject;
class Renderer{
  public:
    void SetCamera(Camera* cam);
    Camera* camera;
    void Submit(Gameobject* gameobject);
    static void NewFrame();
    Renderer();
};
