#include "material.hpp"

Material::Material(Shader* shader, Mesh* mesh){
	this->shader = shader;
	this->mesh = mesh;
	assert(this->shader != nullptr);
	assert(this->mesh != nullptr);
}
void Material::draw(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection){
	shader->SetMat4("model", model);
	shader->SetMat4("view", view);
	shader->SetMat4("projection", projection);
	mesh->draw();
}
void Material::use(){
	shader->use();
}
