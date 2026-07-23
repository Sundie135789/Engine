#include "headers/shader.hpp"
#include "headers/loadshader.hpp"
#include "headers/log.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
Shader::Shader(std::string vertexPath, std::string fragmentPath){
  this->vertexPath = vertexPath;
  this->fragmentPath = fragmentPath;
  std::string vertexSource = LoadShader(vertexPath);
  std::string fragmentSource = LoadShader(fragmentPath);
  GLuint vertex, fragment;
  vertex = glCreateShader(GL_VERTEX_SHADER);
  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  const char* vertexSrc = vertexSource.c_str();
  const char* fragmentSrc = fragmentSource.c_str();
  glShaderSource(vertex, 1,&vertexSrc,nullptr);
  glShaderSource(fragment, 1,&fragmentSrc, nullptr);
  glCompileShader(vertex);
  GLint success = 0;
  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
  if(success == GL_FALSE){
    GLint logSize = 0;
    glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &logSize);
    char errorLog[logSize];
    glGetShaderInfoLog(vertex, logSize, &logSize,&errorLog[0]);
    Log::Warning("Vertex shader compilation failed!\n" + std::string(&errorLog[0]) + "\n");
  }
  glCompileShader(fragment);
  glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
  if(success == GL_FALSE){
    GLint logSize = 0;
    glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &logSize);
    char errorLog[logSize];
    glGetShaderInfoLog(fragment, logSize, &logSize,&errorLog[0]);
    Log::Warning("Fragment shader compilation failed!\n" + std::string(&errorLog[0]) + "\n");
  }
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertex);
  glAttachShader(shaderProgram, fragment);
  glLinkProgram(shaderProgram);
  glDeleteShader(vertex);
  glDeleteShader(fragment);
}
void Shader::Use(){
  glUseProgram(shaderProgram);
  glm::mat4 projection = glm::perspective(glm::radians(90.0f), 2560.0f/1920.0f, 0.1f, 100.0f);
  //glm::mat4 model(1.0f);
  glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
  glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
  //glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
  glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
}
