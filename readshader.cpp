#include <fstream>
#include <iostream>
#include <cstdlib>
std::string LoadShader(std::string path){
  std::ifstream file(path);
  std::string text;
  if(!file.is_open()){
    std::cout << "Error opening file: " << path << std::endl;
    std::exit(1);
  }
  std::string line;
  while(std::getline(file, line)){
    text += line + "\n";
  }
  file.close();
  return text;
}
