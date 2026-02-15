#include "headers/mesh.hpp"
#include "headers/readshader.hpp"
#include "headers/shader.hpp"
#include "headers/camera.hpp"
#include "headers/transform.hpp"
#include <GL/glew.h>
//GLEW failed issue
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
constexpr int width = 1000, height = 800;
constexpr auto title = "Main";
int main() {
  Camera* maincamera = nullptr;
  float speed = 0.1f; 
  glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  if(!glfwInit()){
    std::cout << "Failed to initialize glfw;";
    return 1;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  GLFWwindow* win = glfwCreateWindow(width, height, title, nullptr, nullptr);
  if(!win){
    glfwTerminate();
    std::cout << "Could not create window";
    return 1;
  }
  glfwMakeContextCurrent(win);
  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if(err != GLEW_OK){
    std::cout << "GLEW FAILED : " << glewGetErrorString(err) << "\n";
    return 1;
  }
  std::cout << "OpenGL version: " << glGetString(GL_VERSION) << "\n";

  if(glewInit() != GLEW_OK){
    std::cout << "GLEW failed\n";
    return 1;
  }
  glViewport(0, 0, width, height);
  std::vector<float> vertices = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.5f, 0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f
  };
  std::vector<unsigned int> indices = {
    0, 1, 2,
    2, 3, 0
  };
  std::string vertexPath = "shaders/vertex.glsl", fragmentPath = "shaders/fragment.glsl"; 
  std::string vertexShader = ReadShader(vertexPath);
  std::string fragmentShader = ReadShader(fragmentPath);

  // mild error checks (upto taste, no more than 4 grams)
  // shader  somehow teleported to dustbin
  if(vertexShader == "" || fragmentShader == ""){
    exit(EXIT_FAILURE);
  }
  
  Shader shader(vertexShader, fragmentShader);
  Mesh mesh(vertices,indices, 4);
  shader.use();
  maincamera = new Camera();
  GLuint viewLocation = glGetUniformLocation(shader.shaderProgram, "view"); 
  GLuint projLocation = glGetUniformLocation(shader.shaderProgram, "projection");
  glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(maincamera->viewMatrix));
  glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(maincamera->getProjectionMatrix()));
  bool running = true;
  double lastTime = glfwGetTime();
  while(!glfwWindowShouldClose(win)){
    double currentTime = glfwGetTime();
    float deltaTime = currentTime - lastTime;
    lastTime = currentTime;
    float movespeed = speed * deltaTime * 60.0f;
    
    if(glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS) maincamera->cameraPos.z -= movespeed;
    if(glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS) maincamera->cameraPos.z += movespeed;
    if(glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS) maincamera->cameraPos.x -= movespeed;
    if(glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS) maincamera->cameraPos.x += movespeed;
    maincamera->updateViewMatrix();
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(maincamera->viewMatrix));
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    mesh.Draw();
    glfwSwapBuffers(win);
    glfwPollEvents();
  }
  glfwDestroyWindow(win);
  glfwTerminate();
  return 0;
}
