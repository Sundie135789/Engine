#include "headers/renderer.hpp"
#include "headers/gameobject.hpp"
#include "headers/mesh.hpp"
#include "headers/material.hpp"
#include "headers/shader.hpp"
#include "headers/texture.hpp"
#include "headers/camera.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
Renderer::Renderer(){
  std::cout << "Renderer created successfully!" << std::endl;
}
void Renderer::SetCamera(Camera* cam){
  this->camera = cam;
}
void Renderer::Submit(Gameobject* gameobject){
  if(!camera || !gameobject || !gameobject->mesh || !gameobject->material || !gameobject->material->shader)
  {
    std::cout << "Renderer::Submit -> null pointer" << std::endl;
    std::exit(0);
  }
  glBindVertexArray(gameobject->mesh->vao);
  glUseProgram(gameobject->material->shader->shaderProgram);
  //Set Uniforms
  glm::mat4 model = gameobject->getModelMatrix(gameobject->transform);
  glm::mat4 view = camera->GetViewMatrix();
  glm::mat4 projection = camera->GetProjectionMatrix();
  glUniformMatrix4fv(glGetUniformLocation(gameobject->material->shader->shaderProgram, "model"),1, GL_FALSE, glm::value_ptr(model));
  glUniformMatrix4fv(glGetUniformLocation(gameobject->material->shader->shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
  glUniformMatrix4fv(glGetUniformLocation(gameobject->material->shader->shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
  gameobject->material->texture->Bind();
  glUniform1i(glGetUniformLocation(gameobject->material->shader->shaderProgram, "u_Texture"), 0);

  //Lighting uniforms
  glm::vec3 dir = glm::normalize(glm::vec3(0.3f, 0.8f, 0.4f));
  glUniform3f(glGetUniformLocation(gameobject->material->shader->shaderProgram, "lightDirection"), dir.x, dir.y, dir.z);
  gameobject->mesh->Draw();
}
void Renderer::NewFrame(){
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
