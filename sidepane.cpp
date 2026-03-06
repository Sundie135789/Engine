#include "headers/sidepane.hpp"
#include "headers/shader.hpp"
#include "headers/readshader.hpp"
#include <glm/gtc/matrix_transform.hpp>
#define WINDOW_WIDTH 2560
#define WINDOW_HEIGHT 1920
GLuint sidePaneVAO = 0;
GLuint sidePaneShaderProgram = 0;
GLuint commandFieldVAO = 0;
Shader* commandFieldShader = nullptr;
//GLuint commandFieldShaderProgram = 0;
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
void loadCommandField(){
  float x = 2100.0f, y = 1835.0f;
  float w = 420.0f, h = 60.0f;

  float vertices[] = {
    x, y,
    x+w,y,
    x+w,y+h,
    x,y+h
  };
  GLuint commandFieldVBO;
  glGenBuffers(1, &commandFieldVBO);
  glGenVertexArrays(1, &commandFieldVAO);
  glBindVertexArray(commandFieldVAO);
  glBindBuffer(GL_ARRAY_BUFFER, commandFieldVBO);
  glBufferData(GL_ARRAY_BUFFER, 8 *sizeof(float), vertices , GL_DYNAMIC_DRAW);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 *sizeof(float), 0);
  glEnableVertexAttribArray(0);
  glBindVertexArray(0);
  
  commandFieldShader = new Shader("shaders/ui.vert", "shaders/ui.frag");
  commandFieldShader->use();
  // Set Orthographic projection to the perspective uniform, and set color to uniform vec3 uColor
  const glm::mat4 commandFieldOrtho = glm::ortho(0.0f, (float) WINDOW_WIDTH, (float)WINDOW_HEIGHT, 0.0f,-1.0f, 1.0f);
  glUniformMatrix4fv(glGetUniformLocation(commandFieldShader->shaderProgram, "projection"),1,GL_FALSE, &commandFieldOrtho[0][0]);
  // now set color to uniform vec3 uColor
  glUniform3f(glGetUniformLocation(commandFieldShader->shaderProgram, "uColor"),0.675f, 0.086f, 0.173f);
}
