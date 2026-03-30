#pragma once
#include <GL/glew.h>
#include <string>
#include "texture.hpp"
#include <glm/glm.hpp>
		struct UniformInfo{
			GLint location;
			GLenum type;
			std::string name;
		};
class Shader{
  public:
		GLuint shaderProgram;
		Shader(std::string vertPath, std::string fragPath);
		~Shader();
	
		std::unordered_map<std::string, UniformInfo> uniforms;
		void use();
		void SetColor(float red, float green, float blue);
		void SetTexture(Texture* texture);

		void SetMat4(std::string uniformName, glm::mat4 matrix);
		void SetMat3(std::string uniformName, glm::mat3 matrix);
		void SetVec3(std::string uniformName, glm::vec3 value);
		void SetVec4(std::string uniformName, glm::vec4 value);
		void SetFloat(std::string uniformName, float value);
		void SetInt(std::string uniformName, GLuint value);
};
