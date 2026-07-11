#include "headers/assetmanager.hpp"
#include "headers/globals.hpp"
void AssetManager::CleanUp(){
  for(Texture* texture : g_LoadedTextures){
    if(texture != nullptr){
      delete texture;
    }
  }
}
