#pragma once
#include "shader.hpp"
#include "mesh.hpp"
#include <unordered_map>
#include <string>
class Material{
	public:
	void setFloat(const std::string& name, float value);
	void setVec3(const std::string& name, glm::vec3 value);
	void setMat4(const std::string& name, glm::mat4 value);
	void setTexture(const std::string& name, GLuint value);
	Shader* shader;
	Mesh* mesh;
	Material(Shader* shader, Mesh* mesh);
	void draw(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection);
};
