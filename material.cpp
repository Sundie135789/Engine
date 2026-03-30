#include "material.hpp"

Material::Material(Shader* shader, Mesh* mesh){
	this->shader = shader;
	this->mesh = mesh;
	assert(this->shader != nullptr);
	assert(this->mesh != nullptr);
}
void Material::draw(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection){
	shader->use();
	shader->SetMat4("model", model);
	shader->SetMat4("view", view);
	shader->SetMat4("projection", projection);
	mesh->draw();
}
void Material::setVec3(const std::string& name, glm::vec3 value){
	shader->SetVec3(name, value);
}
void Material::setFloat(const std::string& name, float value){
	shader->SetFloat(name, value);
}
void Material::setMat4(const std::string& name, glm::mat4 value){
	shader->SetMat4(name, value);
}
void Material::setTexture(const std::string& name, GLuint value){
	shader->SetInt(name, value);
}
