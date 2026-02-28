#include "sidepane.hpp"
#include "shader.hpp"
#include "readshader.hpp"

GLuint sidePaneVAO = 0;
GLuint sidePaneShaderProgram = 0;
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
  GLuint vbo, ebo;
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

  std::string vertexShaderLoaded = LoadShader("shaders/sidepane.vert");
  std::string fragmentShaderLoaded = LoadShader("shaders/sidepane.frag");
  const char* vertexSource = vertexShaderLoaded.c_str();
  const char* fragmentSource = fragmentShaderLoaded.c_str();


  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexSource, NULL);
  glCompileShader(vertexShader);
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
  glCompileShader(fragmentShader);

  sidePaneShaderProgram = glCreateProgram();
  glAttachShader(sidePaneShaderProgram, vertexShader);
  glAttachShader(sidePaneShaderProgram, fragmentShader);
  glLinkProgram(sidePaneShaderProgram);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}
