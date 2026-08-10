#include "headers/material.hpp"
#include "headers/assetmanager.hpp"
#include <memory.h>
// Fully defined material
Material::Material(
    std::string albedoTexture,
    std::string metallicTexture,
    std::string roughnessTexture,
    glm::vec3 albedoValue,
    float roughnessValue,
    float metallicValue,
    std::string vertexPath,
    std::string fragmentPath
                ) :
      shader(vertexPath, fragmentPath),
      albedoTexture(AssetManager::GetTexture(albedoTexture)),
      metallicTexture(AssetManager::GetTexture(metallicTexture)),
      roughnessTexture(AssetManager::GetTexture(roughnessTexture)),
      albedoValue(albedoValue),
      roughnessValue(roughnessValue),
      metallicValue(metallicValue),
      tiling(1.0f)
{
}


void Material::setShader(Shader&& shader) {
    this->shader = std::move(shader);
}
void Material::setAlbedoPath(const std::string& albedoPath){
  this->albedoTexture = AssetManager::GetTexture(albedoPath);
}
void Material::setAlbedoValue(const glm::vec3& albedo){
  this->albedoValue = albedo;
}
void Material::setMetallicValue(float metallic){
  this->metallicValue = metallic;
}
void Material::setRoughnessValue(float roughness){
  this->roughnessValue = roughness;
}
void Material::setMetallicPath(const std::string& metallicPath){
  this->metallicTexture = AssetManager::GetTexture(metallicPath);
}
void Material::setRoughnessPath(const std::string& roughnessPath){
  this->roughnessTexture = AssetManager::GetTexture(roughnessPath);
}
