#include"assets/imgui.h"
#include"assets/imgui_impl_glfw.h"
#include"assets/imgui_impl_opengl3.h"
#include "gameobject.hpp"
#include "material.hpp"
#include <string>
#include <cstring>
#include <iostream>
#include "global.hpp"
//make sure object menu function toggles instead of only creating a new window.
GameObject::GameObject(std::string name, Material* material, Transform* transform){
  this->name = name;
	this->material = material;
  this->transform = transform;
  this->material->use();
}
void GameObject::toggleObjectMenu(){
	const char* objectName = this->name.c_str();
	ImGui::SetNextWindowSize(ImVec2(600, 1900), ImGuiCond_Always);
	ImGui::SetNextWindowPos(ImVec2(2000, 0), ImGuiCond_Always);
	ImGui::Begin(objectName);
	ImGui::SetWindowFontScale(1.5f);
	ImGui::Text("Transforms");
	if(ImGui::InputFloat("Pos X", &posX)){
		this->transform->position[0] = posX;
	}
	if(ImGui::InputFloat("Pos Y", &posY)){
		this->transform->position[1] = posY;
	}
	if(ImGui::InputFloat("Pos Z", &posZ)){
		this->transform->position[2] = posZ;
	}
	ImGui::Text("\n");
	if(ImGui::InputFloat("Scale X", &scaleX)){
		this->transform->scale[0] = scaleX;
	}	if(ImGui::InputFloat("Scale Y", &scaleY)){
		this->transform->scale[1] = scaleY;
	}	if(ImGui::InputFloat("Scale Z", &scaleZ)){
		this->transform->scale[2] = scaleZ;
	}
	ImGui::End();
}
GameObject::GameObject(std::string name){
  this->name = name;
	this->material = nullptr;
}

void GameObject::SetMaterial(Material* material){
  this->material = material;
}
void GameObject::SetName(std::string newName){
  this->name = newName;
}
void GameObject::SetTransform(Transform* transform){
  this->transform = transform;
}
GameObject::~GameObject(){
	delete material;
	delete transform;
}
void GameObject::draw(Camera& camera){
  if(this->material == nullptr){
    std::cout << "GameObject.name: " << this->name << "\nDraw call without setting material." << std::endl;
    goTerminate();
    std::exit(1);
  }
  /*shader->use();
  shader->SetMat4("view", camera.GetViewMatrix());
  shader->SetMat4("projection", camera.GetProjectionMatrix());
  glm::mat4 model = transform->GetModelMatrix();
  shader->SetMat4("model", model);
  mesh->draw();*/
	assert(material != nullptr);
	assert(transform != nullptr);
	assert(&camera != nullptr);
	material->use();
	material->draw(transform->GetModelMatrix(), camera.GetViewMatrix(), camera.GetProjectionMatrix());
}
