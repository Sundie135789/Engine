#include "shader.hpp"
#include <cassert>
#include "readfile.hpp"
#include "global.hpp"
#include <vector>
#include <iostream>
Shader::Shader(std::string vertPath, std::string fragPath){
  std::string vertexSource = LoadFile(vertPath);
  std::string fragmentSource = LoadFile(fragPath);
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
  glLinkProgram(shaderProgram);
	GLint uniformCount;
	glGetProgramiv(shaderProgram, GL_ACTIVE_UNIFORMS, &uniformCount);
	for(GLint i =0;i<uniformCount;i++){
		char name[256];
		GLsizei nameLength;
		GLint size;
		GLenum type;
		glGetActiveUniform(shaderProgram, i, sizeof(name), &nameLength, &size, &type, name);
		GLint location = glGetUniformLocation(shaderProgram, name);
		uniforms[std::string(name)] = {location, type, std::string(name)};
	}
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader); 
}
/*void Shader::SetColor(float red, float green, float blue){
  this->red = red;
  this->green = green;
  this->blue = blue;
  hasColor = true;
}*/
void Shader::use(){

  assert(shaderProgram != 0 );
  glUseProgram(shaderProgram);
}

void Shader::SetMat4(std::string uniformName, glm::mat4 set){
  const char* name = uniformName.c_str();
  glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name), 1, GL_FALSE, &set[0][0]);
}
void Shader::SetMat3(std::string uniformName, glm::mat3 set){
  const char* name = uniformName.c_str();
  glUniformMatrix3fv(glGetUniformLocation(shaderProgram, name), 1, GL_FALSE, &set[0][0]);
}
void Shader::SetVec3(std::string uniformName, glm::vec3 set){
  const char* name = uniformName.c_str();
  glUniform3f(glGetUniformLocation(shaderProgram, name), set.x, set.y, set.z);
}
void Shader::SetVec4(std::string uniformName, glm::vec4 set){
  const char* name = uniformName.c_str();
  glUniform4f(glGetUniformLocation(shaderProgram, name), set.x, set.y, set.z, set.w);
}
void Shader::SetFloat(std::string uniformName, float value){
  const char* name = uniformName.c_str();
	glUniform1f(glGetUniformLocation(shaderProgram, name), value);
}
void Shader::SetInt(std::string uniformName, GLuint value){
  const char* name = uniformName.c_str();
	glUniform1i(glGetUniformLocation(shaderProgram, name), value);
}
Shader::~Shader(){
  glDeleteProgram(shaderProgram);
}
