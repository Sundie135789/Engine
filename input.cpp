#include "headers/input.hpp"
#include <glm/geometric.hpp>
#include "headers/window.hpp"
#include "headers/camera.hpp"
#include "headers/globals.hpp"
#include "headers/log.hpp"
#include <GLFW/glfw3.h>
double Input::mouseX = 0.0f;
double Input::mouseY = 0.0f;
std::vector<Input::Keybind>* Input::gameKeybinds = new std::vector<Input::Keybind>();
void Input::ProcessMouseLook(bool& firstMouse, float& lastX, float& lastY, Camera* camera, Window* window){
  window->GetCursorPos(mouseX, mouseY);
  if(firstMouse)
  {
    lastX  = mouseX;
    lastY = mouseY;
    firstMouse = false;
  }
  float deltaY = lastY - mouseY;
  float deltaX = mouseX - lastX;
  lastX = mouseX;
  lastY = mouseY;
  camera->yaw += deltaX * settings.controls.sensitivity;
  camera->pitch += deltaY * settings.controls.sensitivity;
  glm::vec3 direction(
      cos(glm::radians(camera->yaw)) * cos(glm::radians(camera->pitch)),
      sin(glm::radians(camera->pitch)),
      sin(glm::radians(camera->yaw)) * cos(glm::radians(camera->pitch))
      );
  camera->front = glm::normalize(direction);
}
void Input::WASDMouse(bool& firstMouse, float& lastX,float& lastY, Camera* camera, Window* window, float deltaTime){
    Input::ProcessMouseLook(firstMouse, lastX, lastY, camera, window);
    float speed = settings.controls.camera_speed * deltaTime;
    glm::vec3 flatFront = glm::normalize(glm::vec3(camera->front.x, 0.0f, camera->front.z));
    glm::vec3 right = glm::normalize(glm::cross(camera->front, glm::vec3(0,1,0)));
    if(window->GetKey(GLFW_KEY_W))   camera->position += flatFront * speed;
    if(window->GetKey(GLFW_KEY_S))  camera->position -= flatFront * speed;
    if(window->GetKey(GLFW_KEY_D))  camera->position += right * speed;
    if(window->GetKey(GLFW_KEY_A))  camera->position -= right * speed;
    if(window->GetKey(GLFW_KEY_E)) camera->position.y += speed;
    if(window->GetKey(GLFW_KEY_Q)) camera->position.y -= speed;
}
void Input::HandleEngineInput(Window* window,Camera* editorCamera , float deltaTime, float& lastX, float& lastY, bool& firstMouse){
  if(window->GetMouseButton(GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS){

    window->setCursorMode(GLFW_CURSOR_DISABLED);
    Input::WASDMouse(firstMouse, lastX, lastY, editorCamera, window, deltaTime);
  }else {
    window->setCursorMode(GLFW_CURSOR_NORMAL);
    firstMouse = true;
  }
}
void Input::HandleGameInput(Window* window, Camera* gameCamera, float deltaTime, float &lastX, float &lastY, bool &firstMouse){
  window->setCursorMode(GLFW_CURSOR_DISABLED);
  Input::ProcessMouseLook(firstMouse, lastX, lastY, gameCamera, window);
  float speed = settings.controls.camera_speed * deltaTime;
  glm::vec3 flatFront = glm::normalize(glm::vec3(gameCamera->front.x, 0.0f, gameCamera->front.z));
  glm::vec3 right = glm::normalize(glm::cross(gameCamera->front, glm::vec3(0,1,0)));
  if(Input::gameKeybinds->at(0).assignedKey && ImGui::IsKeyDown(Input::gameKeybinds->at(0).assignedKey)){
    gameCamera->position += flatFront * speed;
  }
  if(Input::gameKeybinds->at(1).assignedKey && ImGui::IsKeyDown(Input::gameKeybinds->at(1).assignedKey)){
    gameCamera->position -= flatFront * speed;
  }
  if(Input::gameKeybinds->at(2).assignedKey && ImGui::IsKeyDown(Input::gameKeybinds->at(2).assignedKey)){
    gameCamera->position += right * speed;
  }
  if(Input::gameKeybinds->at(3).assignedKey && ImGui::IsKeyDown(Input::gameKeybinds->at(3).assignedKey)){
    gameCamera->position -= right * speed;
  }
  if(Input::gameKeybinds->at(4).assignedKey && ImGui::IsKeyDown(Input::gameKeybinds->at(4).assignedKey)){
    gameCamera->position.y += 3.0f; // TODO
  }
}

void Input::PopulateKeybinds(){
  Input::gameKeybinds->push_back(Keybind{"Move Forward", ImGuiKey_None, false});
  Input::gameKeybinds->push_back(Keybind{"Move Backwards", ImGuiKey_None, false});
  Input::gameKeybinds->push_back(Keybind{"Move Right", ImGuiKey_None, false});
  Input::gameKeybinds->push_back(Keybind{"Move Left", ImGuiKey_None, false});
  Input::gameKeybinds->push_back(Keybind{"Jump", ImGuiKey_None, false});
}

