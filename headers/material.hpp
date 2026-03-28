#pragma once
#include "shader.hpp"
#include "mesh.hpp"
class Material{
	public:
	Shader* shader;
	Mesh* mesh;
	Material(Shader* shader, Mesh* mesh);
	void use();
	void draw(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection);
};
