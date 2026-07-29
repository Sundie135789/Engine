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
void Renderer::SetGraphicsUniforms(){
  fboShader->Use();
  GLuint fboShaderProgram = fboShader->shaderProgram;
  glUniform1i(glGetUniformLocation(fboShaderProgram, "chromaticAbberation"), settings.graphics.chromaticAbberation);
  glUniform1i(glGetUniformLocation(fboShaderProgram, "chromaticAbberationStrength"), settings.graphics.chromaticAbberationStrength);
  glUniform1i(glGetUniformLocation(fboShaderProgram, "screenTexture"), 0);
}
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
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2560, 1440, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
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

  // Fetch shader program once
  GLuint goShaderProgram = gameobject->material.shader.shaderProgram;
  //Set Uniforms

  glm::mat4 model = gameobject->getModelMatrix();
  glm::mat4 view = camera->GetViewMatrix();
  glm::mat4 projection = camera->GetProjectionMatrix();
  glUniformMatrix4fv(glGetUniformLocation(goShaderProgram, "model"),1, GL_FALSE, glm::value_ptr(model));
  glUniformMatrix4fv(glGetUniformLocation(goShaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
  glUniformMatrix4fv(glGetUniformLocation(goShaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
  // PBR Uniforms
  bool hasAlbedoTex = gameobject->material.albedoTexture != nullptr && !gameobject->material.albedoTexture->path.empty();
  bool hasRoughnessTex = gameobject->material.roughnessTexture != nullptr && !gameobject->material.roughnessTexture->path.empty();
  bool hasMetallicTex = gameobject->material.metallicTexture != nullptr && !gameobject->material.metallicTexture->path.empty();

  if(hasAlbedoTex) gameobject->material.albedoTexture->Bind(0);
  if(hasRoughnessTex) gameobject->material.roughnessTexture->Bind(1);
  if(hasMetallicTex)gameobject->material.metallicTexture->Bind(2);
  // Set hasTexture booleans
  glUniform1i(glGetUniformLocation(goShaderProgram, "hasAlbedoTex"), hasAlbedoTex);
  glUniform1i(glGetUniformLocation(goShaderProgram, "hasRoughnessTex"), hasRoughnessTex);
  glUniform1i(glGetUniformLocation(goShaderProgram, "hasMetallicTex"), hasMetallicTex);
  // Set primary textures
  glUniform1i(glGetUniformLocation(goShaderProgram, "albedoTexture"), 0);
  glUniform1i(glGetUniformLocation(goShaderProgram, "roughnessTexture"), 1);
  glUniform1i(glGetUniformLocation(goShaderProgram, "metallicTexture"), 2);
  // Set fallback values
  glUniform3fv(glGetUniformLocation(goShaderProgram, "albedoValue"), 1, glm::value_ptr(gameobject->material.albedoValue));
  glUniform1f(glGetUniformLocation(goShaderProgram, "roughnessValue"), gameobject->material.roughnessValue);
  glUniform1f(glGetUniformLocation(goShaderProgram, "metallicValue"), gameobject->material.metallicValue);
  //glUniform1i(glGetUniformLocation(goShaderProgram, "u"), 0);

  //Lighting uniforms
  glm::vec3 lightDir = glm::normalize(-light->lightDir);
  glUniform3f(glGetUniformLocation(goShaderProgram, "lightDirection"), lightDir.x, lightDir.y, lightDir.z);
  glUniform3f(glGetUniformLocation(goShaderProgram, "viewPos"), camera->position.x, camera->position.y, camera->position.z);
  gameobject->mesh.Draw();
  //glUniform1i(glGetUniformLocation(goShaderProgram, "bloom"), settings.graphics.bloom);
  //fetch framebuffer shader program once
}
void Renderer::NewFrame(){
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

