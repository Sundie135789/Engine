#include "sidepane.hpp"
#include "shader.hpp"
GLuint sidePaneVAO = 0;
Shader* sidePaneShader = nullptr;
void loadSidePane(){
  float vertices[] = {
    0.6f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    0.6f, 1.0f, 0.0f
  };
  unsigned int indices[] = {
    0, 1, 2,
    0, 2, 3
  };
  GLuint vbo,  ebo;
  glGenBuffers(1, &vbo);
  glGenVertexArrays(1, &sidePaneVAO);
  glGenBuffers(1, &ebo);

  glBindVertexArray(sidePaneVAO);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
  
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glBindVertexArray(0);
  sidePaneShader = new Shader("shaders/plain.vert", "shaders/plain.frag");
  sidePaneShader->SetColor(0.133333f, 0.133333f, 0.133333f);
}
