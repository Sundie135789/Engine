#include "headers/renderer.hpp"
#include "headers/gameobject.hpp"
#include "headers/mesh.hpp"
#include "headers/log.hpp"
#include "headers/material.hpp"
#include "headers/shader.hpp"
#include "headers/texture.hpp"
#include "headers/camera.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
Renderer::Renderer(){
  Log::Success("Renderer created successfully!");
}
void Renderer::SetLight(DirectionalLight* light){
  this->light = light;
}
void Renderer::SetCamera(Camera* cam){
  this->camera = cam;
}
void Renderer::Submit(Gameobject* gameobject){
  if(!camera ||  !gameobject || gameobject->mesh.vertices.empty())
  {
    Log::Fatal("[ERROR] Renderer::Submit -> null pointer\n");
    std::exit(1);
  }
  glBindVertexArray(gameobject->mesh.vao);
  gameobject->material.shader.Use();
  //glUseProgram(gameobject->material.shader.shaderProgram);
  //Set Uniforms
  glm::mat4 model = gameobject->getModelMatrix();
  glm::mat4 view = camera->GetViewMatrix();
  glm::mat4 projection = camera->GetProjectionMatrix();
  glUniformMatrix4fv(glGetUniformLocation(gameobject->material.shader.shaderProgram, "model"),1, GL_FALSE, glm::value_ptr(model));
  glUniformMatrix4fv(glGetUniformLocation(gameobject->material.shader.shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
  glUniformMatrix4fv(glGetUniformLocation(gameobject->material.shader.shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
  gameobject->material.texture->Bind(0);
  glUniform1i(glGetUniformLocation(gameobject->material.shader.shaderProgram, "u_Texture"), 0);
  glUniform3fv(glGetUniformLocation(gameobject->material.shader.shaderProgram, "materialColor"), 1, glm::value_ptr(gameobject->material.color));

  //Lighting uniforms
  glm::vec3 lightDir = glm::normalize(-light->lightDir);
  glUniform3f(glGetUniformLocation(gameobject->material.shader.shaderProgram, "lightDirection"), lightDir.x, lightDir.y, lightDir.z);
  glUniform1f(glGetUniformLocation(gameobject->material.shader.shaderProgram, "shininess"), gameobject->material.shininess);
  glUniform3f(glGetUniformLocation(gameobject->material.shader.shaderProgram, "viewPos"), camera->position.x, camera->position.y, camera->position.z);
  // Specular uniforms
  glUniform3fv(glGetUniformLocation(gameobject->material.shader.shaderProgram, "specularColor"), 1,glm::value_ptr(gameobject->material.specularColor));    
  glUniform1f(glGetUniformLocation(gameobject->material.shader.shaderProgram, "specularStrength"), gameobject->material.specularStrength);
  gameobject->mesh.Draw();
}
void Renderer::NewFrame(){
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
