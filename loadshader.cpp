#include "headers/loadshader.hpp"
#include <fstream>
#include <string>
#include <iostream>
std::string LoadShader(std::string path){
  std::ifstream file(path);
  std::string filetext, line;
  while(std::getline(file, line))
    filetext += line + '\n';
  std::cout << "Shader loaded: " << path << '\n'; 
  return filetext;
}
