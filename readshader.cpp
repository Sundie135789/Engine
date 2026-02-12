#include <fstream>
#include <string>
#include "headers/readshader.hpp"
#include <iostream>
std::string ReadShader(std::string path){
  std::ifstream file(path);
  if(!file.is_open()) {
     std::cout << "(Shader) Failed to open file: ";
     std::cout << "(Shader) Exiting...";
     return "";
  }
  std::string line, file_text;
  while(getline(file, line)){
    file_text += line + '\n';
  }
  return file_text;
}
