#include "headers/input.hpp"
#include <iostream>
#include "headers/window.hpp"
#include "headers/camera.hpp"
#include "headers/globals.hpp"
#include <GLFW/glfw3.h>
double Input::mouseX = 0.0f;
double Input::mouseY = 0.0f;
bool Input::standardWASDMouse = false;
void Input::WASDMouse(bool& firstMouse, float& lastX,float& lastY, Camera* camera, Window* window, float deltaTime){
  window->GetCursorPos(mouseX, mouseY);
    if(firstMouse)
    {  
      lastX = mouseX;
      lastY = mouseY;
      firstMouse = false;
    }
    float deltaY = lastY - mouseY;
    float deltaX = mouseX - lastX;
    lastX = mouseX;
    lastY = mouseY;
    camera->yaw += deltaX * sensitivity;
    camera->pitch += deltaY * sensitivity;
    glm::vec3 direction;
    direction.x = cos(glm::radians(camera->yaw)) * cos(glm::radians(camera->pitch));
    direction.y = sin(glm::radians(camera->pitch));
    direction.z = sin(glm::radians(camera->yaw)) * cos(glm::radians(camera->pitch));
    camera->front = glm::normalize(direction);
    float speed = camera_speed * deltaTime;
    glm::vec3 flatFront = glm::normalize(glm::vec3(camera->front.x, 0.0f, camera->front.z));
    glm::vec3 right = glm::normalize(glm::cross(camera->front, glm::vec3(0,1,0)));
    if(window->GetKey(GLFW_KEY_W))   camera->position += flatFront * speed;
    if(window->GetKey(GLFW_KEY_S))  camera->position -= flatFront * speed;
    if(window->GetKey(GLFW_KEY_D))  camera->position += right * speed;
    if(window->GetKey(GLFW_KEY_A))  camera->position -= right * speed;

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
  if(Input::standardWASDMouse)
  {
  //  std::cout << "Input standardWASDMouse";
    Input::WASDMouse(firstMouse, lastX, lastY, gameCamera, window, deltaTime);
  }
}


