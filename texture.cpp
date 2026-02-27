#include "texture.hpp"
#include <cstdlib>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "global.hpp"

 Texture::Texture(std::string imagePath){
  int width, height, channels;
  
  unsigned char* image = stbi_load(imagePath.c_str(), &width, &height, &channels, 0);
  if(image == NULL){
    std::cout << "Error in loading image: " << imagePath << std::endl;
    goTerminate();
    std::exit(1);
  }
  glGenTextures(1, &textureID);  
  glBindTexture(GL_TEXTURE_2D, textureID);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;
  glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image);
  glGenerateMipmap(GL_TEXTURE_2D);
  stbi_image_free(image);
  glBindTexture(GL_TEXTURE_2D, 0);
}
Texture::~Texture(){
  glDeleteTextures(1, &textureID);
  //stbi_image_free(&(this->texture));
}
