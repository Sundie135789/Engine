#include "headers/input.hpp"
#include "headers/window.hpp"
#include "headers/camera.hpp"
#include <glm/trigonometric.hpp>
double Input::mouseX = 0.0f;
double Input::mouseY = 0.0f;
void Input::HandleEngineInput(Window* window,Camera* editorCamera, float deltaTime, float lastX, float lastY, bool firstMouse){
  window->GetCursorPos(mouseX, mouseY);
  float deltaX = mouseX - lastX;
  float deltaY = lastY - mouseY;
  if(firstMouse)
  {
    lastX = mouseX;
    lastY = mouseY;
    firstMouse = false;
  }
  lastX = mouseX;
  lastY = mouseY;
  editorCamera->yaw += deltaX * SENSITIVITY;
  editorCamera->pitch += deltaY * SENSITIVITY;
  glm::vec3 direction;
  direction.x = cos(glm::radians(editorCamera->yaw) * cos(glm::radians(editorCamera->pitch)));
  direction.y = sin(glm::radians(editorCamera->pitch));
  direction.z = sin(glm::radians(editorCamera->yaw * cos(glm::radians(editorCamera->pitch))));
  editorCamera->front = glm::normalize(direction);
  float speed = ENGINE_CAMERA_SPEED * deltaTime;
  glm::vec3 flatFront = glm::normalize(glm::vec3(editorCamera->front.x, 0.0f, editorCamera->front.z));
  glm::vec3 right = glm::normalize(glm::cross(editorCamera->front, glm::vec3(0,1,0)));
  if(window->GetKey(GLFW_KEY_W))   editorCamera->position += flatFront * speed;
  if(window->GetKey(GLFW_KEY_S))  editorCamera->position -= flatFront * speed;
  if(window->GetKey(GLFW_KEY_D))  editorCamera->position -= right * speed;
  if(window->GetKey(GLFW_KEY_A))  editorCamera->position += right * speed;
 
}
void Input::HandleGameInput(){
  //TODO
}

/*
 *  void processInput(GLFWwindow* window, float deltaTime){
  if(mainWindow->GetCursorMode() != GLFW_CURSOR_DISABLED) 
    return;
  double mouseX, mouseY;
  mainWindow->GetCursorPos(mouseX, mouseY);

  float deltaX = mouseX - lastX;
  float deltaY = lastY - mouseY; 
  if(firstMouse)
  {
    lastX = mouseX;
    lastY = mouseY;
    firstMouse = false;
  }
  lastX = mouseX;
  lastY = mouseY;
  editorCamera->yaw += deltaX * SENSITIVITY;
  editorCamera->pitch += deltaY * SENSITIVITY;
  glm::vec3 direction;
  direction.x = cos(glm::radians(editorCamera->yaw) * cos(glm::radians(editorCamera->pitch)));
  direction.y = sin(glm::radians(editorCamera->pitch));
  direction.z = sin(glm::radians(editorCamera->yaw) * cos(glm::radians(editorCamera->pitch)));
  editorCamera->front = glm::normalize(direction);
  float speed = USER_SPEED * deltaTime;
  glm::vec3 flatFront = glm::normalize(glm::vec3(editorCamera->front.x, 0.0f, editorCamera->front.z));
  glm::vec3 right = glm::normalize(glm::cross(editorCamera->front, glm::vec3(0,1,0)));
  if(mainWindow->GetKey(GLFW_KEY_W))   editorCamera->position += flatFront * speed;
  if(mainWindow->GetKey(GLFW_KEY_S))  editorCamera->position -= flatFront * speed;
  if(mainWindow->GetKey(GLFW_KEY_D))  editorCamera->position -= right * speed;
  if(mainWindow->GetKey(GLFW_KEY_A))  editorCamera->position += right * speed;
}
 *
 *
 *
 * */
