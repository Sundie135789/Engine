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
#include "text.hpp"
#include <fstream>
#include "stb_image.h"
#define STB_IMAGE_IMPLEMENTATION
#define WINDOW_WIDTH 2560
#define WINDOW_HEIGHT 1920
/*
 * Create a global LoadFont function to parse .fnt file and load atlas texture.
 * */
std::vector<GameObject*> gameobjects;
std::string commandBuffer = "";
bool LoadFont(const std::string& fntFile, const std::string& atlasFile){
  std::ifstream file(fntFile);
  if(!file.is_open()) return false;
  std::string line;
  while(std::getline(file, line)){
    if(line.find("char id=") == 0){
      int id,x,y,width,height,xOffset,yOffset,xAdvance;
      sscanf(line.c_str(), "char id=%d x=%d y=%d width=%d height=%d xoffset=%d yoffset=%d xadvance=%d",
          &id, &x, &y, &width, &height, &xOffset, &yOffset, &xAdvance);
      Character ch((char)id,x,y,width,height,xOffset,yOffset,xAdvance);
      fontCharacters[(char)id] = ch;
    }
    else if (line.find("common ") == 0){
      sscanf(line.c_str(), "common lineHeight=%d", &fontLineHeight);
    }
  }
  file.close();

  int width, height, channels;
  unsigned char* data = stbi_load(atlasFile.c_str(), &width, &height, &channels, 0);
  if(!data) return false;
  glGenTextures(1,&fontTextureID);
  glBindTexture(GL_TEXTURE_2D, fontTextureID);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  stbi_image_free(data);
  return true;
}
void RenderText(std::string text, float x, float y, float scale, glm::vec3 color){
  
}
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
  Camera* mainCamera = new Camera((float)WINDOW_WIDTH/WINDOW_HEIGHT);
  loadSidePane();
  LoadFont("assets/font.fnt", "assets/font.png");
  Shader* textShader = new Shader("shaders/text.vert", "shaders/text.frag");
  glm::mat4 textOrtho = glm::ortho(0.0f, (float) WINDOW_WIDTH, (float)WINDOW_HEIGHT, 0.0f,-1.0f, 1.0f);
  textShader->use();
  textShader->SetMatrix("projection", textOrtho);
  initTextRender();
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
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
    glDisable(GL_DEPTH_TEST);
    float color[] = {1.0f, 1.0f, 1.0f};
    renderText(*textShader, "Hello SundieCoder!", 50.0f, WINDOW_HEIGHT - 50.0f, 1.0f, color);
    glEnable(GL_DEPTH_TEST);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwDestroyWindow(window);
  goTerminate();
  return 0;
}
