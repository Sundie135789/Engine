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
  // PBR Uniforms
  bool hasAlbedoTex = gameobject->material.albedoTexture != nullptr && !gameobject->material.albedoTexture->path.empty();
  bool hasRoughnessTex = gameobject->material.roughnessTexture != nullptr && !gameobject->material.roughnessTexture->path.empty();
  bool hasMetallicTex = gameobject->material.metallicTexture != nullptr && !gameobject->material.metallicTexture->path.empty();

  if(hasAlbedoTex) gameobject->material.albedoTexture->Bind(0);
  if(hasRoughnessTex) gameobject->material.roughnessTexture->Bind(1);
  if(hasMetallicTex)gameobject->material.metallicTexture->Bind(2);
  // Set hasTexture booleans
  glUniform1i(glGetUniformLocation(gameobject->material.shader.shaderProgram, "hasAlbedoTex"), hasAlbedoTex);
  glUniform1i(glGetUniformLocation(gameobject->material.shader.shaderProgram, "hasRoughnessTex"), hasRoughnessTex);
  glUniform1i(glGetUniformLocation(gameobject->material.shader.shaderProgram, "hasMetallicTex"), hasMetallicTex);
  // Set primary textures
  glUniform1i(glGetUniformLocation(gameobject->material.shader.shaderProgram, "albedoTexture"), 0);
  glUniform1i(glGetUniformLocation(gameobject->material.shader.shaderProgram, "roughnessTexture"), 1);
  glUniform1i(glGetUniformLocation(gameobject->material.shader.shaderProgram, "metallicTexture"), 2);
  // Set fallback values
  glUniform3fv(glGetUniformLocation(gameobject->material.shader.shaderProgram, "albedoValue"), 1, glm::value_ptr(gameobject->material.albedoValue));
  glUniform1f(glGetUniformLocation(gameobject->material.shader.shaderProgram, "roughnessValue"), gameobject->material.roughnessValue);
  glUniform1f(glGetUniformLocation(gameobject->material.shader.shaderProgram, "metallicValue"), gameobject->material.metallicValue);
  //glUniform1i(glGetUniformLocation(gameobject->material.shader.shaderProgram, "u"), 0);

  //Lighting uniforms
  glm::vec3 lightDir = glm::normalize(-light->lightDir);
  glUniform3f(glGetUniformLocation(gameobject->material.shader.shaderProgram, "lightDirection"), lightDir.x, lightDir.y, lightDir.z);
  glUniform3f(glGetUniformLocation(gameobject->material.shader.shaderProgram, "viewPos"), camera->position.x, camera->position.y, camera->position.z);
  gameobject->mesh.Draw();
}
void Renderer::NewFrame(){
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

