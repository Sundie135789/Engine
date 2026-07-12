#pragma once
#include "texture.hpp"
#include <string>
class AssetManager{
  public:
    static void Cleanup();
    static Texture* GetTexture(const std::string& path);
};
