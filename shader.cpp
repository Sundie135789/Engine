#include "headers/shader.hpp"
#include <string>
#include <GL/glew.h>
#include <GL/gl.h>
#include "headers/readshader.hpp"
//TODO really big errors. just remove the returnpair system, then find a way to get .size() of a std::string. goodnight. french exam.
Shader::Shader(std::string vertex, std::string fragment){
  
  GLuint fragmentID = glCreateShader(GL_FRAGMENT_SHADER);  
  GLuint vertexID = glCreateShader(GL_VERTEX_SHADER);  
  const char* vertexCode  = vertex.c_str();
  const char* fragmentCode  = fragment.c_str();
  glShaderSource(fragmentID, 1,&fragmentCode, nullptr);
  glShaderSource(vertexID, 1, &vertexCode, nullptr);
  glCompileShader(fragmentID);
  glCompileShader(vertexID);
  this->shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, fragmentID);
  glAttachShader(shaderProgram, vertexID);
  glLinkProgram(shaderProgram);
  glDeleteShader(fragmentID);
  glDeleteShader(vertexID);
}
void Shader::use(){
  glUseProgram(this->shaderProgram);
}
Shader::~Shader(){
  glDeleteProgram(this->shaderProgram);
  
}
