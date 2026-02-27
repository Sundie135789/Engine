#include "shader.hpp"
#include "readshader.hpp"
#include "global.hpp"
#include <vector>
#include <iostream>
Shader::Shader(std::string vertPath, std::string fragPath){
  this->hasColor = false;
  std::string vertexSource = LoadShader(vertPath);
  std::string fragmentSource = LoadShader(fragPath);
  const char* vertexCstr = vertexSource.c_str();
  const char* fragmentCstr = fragmentSource.c_str();

  glCreateShader(GL_VERTEX_SHADER);
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(vertexShader, 1, &(vertexCstr), nullptr);
  glShaderSource(fragmentShader, 1, &(fragmentCstr), nullptr);
  glCompileShader(vertexShader);
  GLint success;
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if(!success){
    GLint logLength;
    glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<char> infoLog(logLength);
    glGetShaderInfoLog(vertexShader, logLength, nullptr, infoLog.data());
    std::cout << "Vertex shader compilation error: \n Path: "<<vertPath << "\n" << infoLog.data() <<"\n";
    goTerminate();
    return;
  }
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if(!success){
    GLint logLength;
    glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<char> infoLog(logLength);
    glGetShaderInfoLog(fragmentShader, logLength, nullptr, infoLog.data());
    std::cout << "Fragment shader compilation error: \n Path: "<< fragPath << "\n" << infoLog.data() <<"\n";
    goTerminate();
    return;
  }
  this->shaderProgram = glCreateProgram();
  std::cout << std::to_string(this->shaderProgram) << std::endl;
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

}
void Shader::SetColor(float red, float green, float blue){
  this->red = red;
  this->green = green;
  this->blue = blue;
  hasColor = true;
}
void Shader::use(){

  glLinkProgram(shaderProgram);
  glUseProgram(shaderProgram);
  if(hasColor == true){
    glUniform3f(glGetUniformLocation(this->shaderProgram, "uColor"), red, green, blue);
  }else{
    glUniform3f(glGetUniformLocation(this->shaderProgram, "uColor"), 0.502f, 0.0f, 0.502f);
  }
}
