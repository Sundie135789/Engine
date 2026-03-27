#pragma once
#include <GL/glew.h>
#include <string>
#include "texture.hpp"
#include <glm/glm.hpp>
class Shader{
  public:
		GLuint shaderProgram;
		Shader(std::string vertPath, std::string fragPath);
		~Shader();
	
		void use();
		void SetColor(float red, float green, float blue);
		void SetTexture(Texture* texture);

		void SetMat4(std::string uniformName, glm::mat4 matrix);
		void SetMat3(std::string uniformName, glm::mat3 matrix);
		void SetVec3(std::string uniformName, glm::vec3 value);
		void SetVec4(std::string uniformName, glm::vec4 value);
		void SetFloat(std::string uniformName, float value);
		void SetInt(std::string uniformName, int value);
};
