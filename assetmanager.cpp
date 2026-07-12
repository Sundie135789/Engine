#include "headers/assetmanager.hpp"
#include "headers/globals.hpp"
void AssetManager::Cleanup(){
  for(Texture* texture : g_loadedTextures){
    if(texture != nullptr){
      delete texture;
    }
  }
}
Texture* AssetManager::GetTexture(const std::string& path){
  for(Texture* texture : g_loadedTextures){
    if(texture->path == path){
      return texture;
    }
  }
  Texture* texture = new Texture(path);
  g_loadedTextures.push_back(texture);
  return texture;
}
