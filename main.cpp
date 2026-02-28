/*
 The model matrix is handled by a Gameobject's Transform class.
 The projection and view matrices require a separate Camera class, even if there is only one Camera (uptill now).
 This is because the code inside a Camera class, written raw inside the main function in main.cpp would be catastrophic for cleanliness;
 * */


/*
 The Font atlas is a PNG file containing all the characters of a font, tightly-packed together.
  We load a font atlas from CPU side to the GPU as GL_TEXTURE_2D.
  Whenever we need a character for rendering, we can look at the fnt data, look at the atlas, and get the character.
  This is how bitmap font texture atlas system works.
 * */
#include <iostream>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include "mesh.hpp"
#include "shader.hpp"
#include "gameobject.hpp"
#include "global.hpp"
#include "texture.hpp"
#include "sidepane.hpp"
#include "transform.hpp"
#include "camera.hpp"
#define WINDOW_WIDTH 2560
#define WINDOW_HEIGHT 1920
/*
 * Create a global LoadFont function to parse .fnt file and load atlas texture.
 * */
std::vector<GameObject*> gameobjects;
std::string commandBuffer = "";
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods){
  if(action != GLFW_PRESS) return;
  if(key >= GLFW_KEY_A && key <= GLFW_KEY_Z){
    char c = 'a' + (key - GLFW_KEY_A);
    commandBuffer += c;
  }else if(key == GLFW_KEY_ENTER){
    //TODO
  }
  std::cout << commandBuffer << '\n';
}
void goTerminate(){
  for(auto g : gameobjects){
    delete g;
  }
  gameobjects.clear();
  glfwTerminate();

}
int main(void){
  Camera* mainCamera = new Camera((float)WINDOW_WIDTH/WINDOW_HEIGHT);

  if(!glfwInit()){
    std::cout << "GLFW Init error" << std::endl;
    goTerminate();
    return 1;
  }
  GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "GameEngine - SundieCoder v1.0", nullptr, nullptr);
  glfwMakeContextCurrent(window);
  glewExperimental = GL_TRUE;
  GLenum glewStatus = glewInit();
  if(glewStatus != GLEW_OK){
    std::cout << "GLEW Init error" << std::endl;
    goTerminate();
    return 1;
  }
  glfwSetKeyCallback(window, key_callback);
  glViewport(0,0,WINDOW_WIDTH, WINDOW_HEIGHT);
  // --- OpenGL Code ---
  loadSidePane();
  float vertices[] = {
    -0.375f, -0.375f, 0.0f, 0.0f, 0.0f,
    0.375f, -0.375f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.375f, 0.0f ,0.5f, 1.0f
  };
  Texture* texture = new Texture("assets/monkey.png");
  Mesh* mesh = new Mesh(vertices, 3, true);
  Shader* shader = new Shader("shaders/texture.vert", "shaders/texture.frag");
  Transform* transform = new Transform();
  //shader->SetColor(0.5f, 0.5f, 0.5f);
  shader->SetTexture(texture);
  //shader->SetTexture(text);
  GameObject* gameobject = new GameObject("triangle");
  gameobject->SetShader(shader);
  gameobject->SetMesh(mesh);
  gameobject->SetTransform(transform);
  gameobjects.push_back(gameobject);
  while(!glfwWindowShouldClose(window)){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT);
    assert(mainCamera != nullptr);
    
    for(GameObject* g : gameobjects){
      g->draw(*mainCamera);
    }
    glUseProgram(sidePaneShaderProgram);
    glBindVertexArray(sidePaneVAO); 
    glUniform3f(glGetUniformLocation(sidePaneShaderProgram, "uColor"), 0.133f, 0.133f, 0.133f);
    glDisable(GL_DEPTH_TEST);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glEnable(GL_DEPTH_TEST);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwDestroyWindow(window);
  goTerminate();
  return 0;
}
