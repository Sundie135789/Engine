#include "headers/loadshader.hpp"
#include "headers/log.hpp"
#include <fstream>
#include <string>
std::string LoadShader(std::string path){
  std::ifstream file(path);
  if(!file){
    // If we cannot load even missing_texture.png, end the program.
    Log::Fatal("Could not find file: "+path+"\nExiting...\n");
    std::exit(1);
  }
  std::string filetext, line;
  while(std::getline(file, line))
    filetext += line + '\n';
  Log::Success("Shader loaded: " +path +'\n'); 
  return filetext;
}
