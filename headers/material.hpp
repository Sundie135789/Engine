#pragma once

#include "shader.hpp"
#include "texture.hpp"
#include <glm/glm.hpp>
#include <string>

class Material {
  public:
    Shader shader;
    Texture* albedoTexture;
    Texture* metallicTexture;
    Texture* roughnessTexture;
    float roughnessValue;
    float metallicValue;
    glm::vec3 albedoValue;
    Material(
             std::string albedoTexture = "",
             std::string metallicTexture = "",
             std::string roughnessTexture = "",
             glm::vec3 albedoValue = { 1.0f, 1.0f, 1.0f},
             float roughnessValue = 0.5f,
             float metallicValue = 0.0f,
             std::string vertexPath = "shaders/basic.vert",
             std::string fragmentPath = "shaders/basic.frag"
             );

    void setShader(Shader&& shader);
    void setAlbedoPath(const std::string& albedoPath);
    void setAlbedoValue(const glm::vec3& albedo);
    void setMetallicValue(float metallic);
    void setRoughnessValue(float roughness);
    void setMetallicPath(const std::string& metallicPath);
    void setRoughnessPath(const std::string& roughnessPath);

};
