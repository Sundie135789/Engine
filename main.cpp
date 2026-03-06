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
//TODO: Top priority: https://wiki.osdev.org/Bare_Bones -> do bootstrap assembly in ~/project/boot/
//TODO: Implement delta timing with V Sync
#include <iostream>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include "headers/mesh.hpp"
#include "headers/shader.hpp"
#include "headers/gameobject.hpp"
#include "headers/global.hpp"
#include "headers/texture.hpp"
#include "headers/sidepane.hpp"
#include "headers/transform.hpp"
#include "headers/camera.hpp"
#include "headers/text.hpp"
#include <fstream>
#include "stb_image.h"
#define WINDOW_WIDTH 2560
#define WINDOW_HEIGHT 1920
std::vector<GameObject*> gameobjects;
std::string commandBuffer = "";
bool LoadFont(const std::string& fntFile, const std::string& atlasFile){
  std::ifstream file(fntFile);
  if(!file.is_open()) return false;
  std::string line;
  while(std::getline(file, line)){
    if(!line.empty() && line.back() == '\r')line.pop_back();
    if(line.find("common ") == 0){
      sscanf(line.c_str(), "common lineHeight=%f base=%*f ascent=%*f descent=%*f scaleW=%d scaleH=%d",
          &fontLineHeight, &fontAtlasWidth, &fontAtlasHeight);
  
    }
    else if(line.find("char id=") == 0){
      int id, x, y, width, height;
      float xOffset, yOffset, xAdvance;
      sscanf(line.c_str(), "char id=%d x=%d y=%d width=%d height=%d xoffset=%f yoffset=%f xadvance=%f",
          &id, &x, &y, &width, &height, &xOffset, &yOffset, &xAdvance);
      Character ch((char) id, x, y, width, height, xOffset, yOffset, xAdvance);
      fontCharacters[(char)id] = ch;
    }
  }
  file.close();
  for(auto& [key,ch] : fontCharacters){
    ch.u0 /=fontAtlasWidth;
    ch.u1 /= fontAtlasWidth;
    ch.v0 /= fontAtlasHeight;
    ch.v1 /= fontAtlasHeight;
  }
  int width, height, channels;
  unsigned short* data = stbi_load_16(atlasFile.c_str(), &width, &height, &channels, 0);
  if(!data) return false;
  glGenTextures(1, &fontTextureID);
  glBindTexture(GL_TEXTURE_2D, fontTextureID);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  glTexImage2D (GL_TEXTURE_2D, 0, GL_R16, width, height, 0,GL_RED, GL_UNSIGNED_SHORT, data);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  stbi_image_free(data);
  return true;

}
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods){
  std::cout << "MOD: " << (char) mods << " AND " << mods;
  if(action != GLFW_PRESS) return;
  if(key >= GLFW_KEY_A && key <= GLFW_KEY_Z){
    char c = 'a' + (key - GLFW_KEY_A);
    commandBuffer += c;
  }else if(key == GLFW_KEY_SPACE){
    commandBuffer += " ";
  }
  else if(key == GLFW_KEY_ENTER){
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
  float command_default_color[] = {0.403f, 0.403f, 0.403f};
  float command_color[] = {0.675, 0.086, 0.173};
  
  Camera* mainCamera = new Camera((float)WINDOW_WIDTH/WINDOW_HEIGHT);
  loadSidePane();
  loadCommandField();
  LoadFont("assets/description.fnt", "assets/font.png");
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
    if (commandBuffer == "") renderText(*textShader, "Enter Command Here...", 2112.5f, WINDOW_HEIGHT - 75.0f, 1.0f, command_default_color);
    else renderText(*textShader, commandBuffer, 2112.5f, WINDOW_HEIGHT-75.0f, 1.0f, command_color);
    glLineWidth(3.0f);
    glBindVertexArray(commandFieldVAO);
    glUseProgram(commandFieldShader->shaderProgram);
    glDrawArrays(GL_LINE_LOOP, 0, 4);
    glEnable(GL_DEPTH_TEST);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwDestroyWindow(window);
  goTerminate();
  return 0;
}
