#include "headers/renderer.hpp"
#include "headers/gameobject.hpp"
#include "headers/mesh.hpp"
#include "headers/log.hpp"
#include "headers/material.hpp"
#include "headers/shader.hpp"
#include "headers/texture.hpp"
#include "headers/camera.hpp"
#include "headers/globals.hpp"
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
void Renderer::FBOSetup(){
  glGenFramebuffers(1, &framebuffer);
  glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

  glGenTextures(1, &textureColorBuffer);
  glBindTexture(GL_TEXTURE_2D, textureColorBuffer);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2560, 1440, 0, GL_RGB, GL_UNSIGNED_INT, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorBuffer, 0);

  unsigned int rbo;
  glGenRenderbuffers(1, &rbo);
  glBindRenderbuffer(GL_RENDERBUFFER, rbo);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 2560, 1440);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
  float quadVertices[] = {
    -1.0f, 1.0f, 0.0f, 1.0f,
    -1.0f, -1.0f, 0.0f, 0.0f,
    1.0f, -1.0f, 1.0f, 0.0f,

    -1.0f, 1.0f, 0.0f, 1.0f,
    1.0f, -1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 1.0f, 1.0f
  };
  unsigned int quadVBO;
  glGenVertexArrays(1, &quadVAO);
  glGenBuffers(1, &quadVBO);
  glBindVertexArray(quadVAO);
  glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2*sizeof(float)));
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

