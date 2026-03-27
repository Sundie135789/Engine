#include"assets/imgui.h"
#include"assets/imgui_impl_glfw.h"
#include"assets/imgui_impl_opengl3.h"
#include "gameobject.hpp"
#include <string>
#include <cstring>
#include <iostream>
#include "global.hpp"
//make sure object menu function toggles instead of only creating a new window.
GameObject::GameObject(std::string name, Shader* shader, Mesh* mesh, Transform* transform){
  this->name = name;
  this->shader = shader;
  this->mesh = mesh;
  this->transform = transform;
  this->shader->use();
	
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
  this->shader = nullptr;
  this->mesh = nullptr;
}
void GameObject::SetShader(Shader *shader){
  this->shader = shader;
}
void GameObject::SetMesh(Mesh *mesh){
  this->mesh = mesh;
}
void GameObject::SetName(std::string newName){
  this->name = newName;
}
void GameObject::SetTransform(Transform* transform){
  this->transform = transform;
}
GameObject::~GameObject(){
  delete mesh;
  delete shader;
	delete transform;
}
void GameObject::draw(Camera& camera){
  if(this->shader == nullptr){
    std::cout << "GameObject.name: " << this->name << "\nGameObject.draw() called without setting shader." << std::endl;
    goTerminate();
    std::exit(1);
  }
  if(this->mesh == nullptr){
    std::cout << "GameObject.name: " << this->name << "\nGameObject.draw() called without setting mesh." << std::endl;
    goTerminate();
    std::exit(1);
  }
  shader->use();
  shader->SetMat4("view", camera.GetViewMatrix());
  shader->SetMat4("projection", camera.GetProjectionMatrix());
  glm::mat4 model = transform->GetModelMatrix();
  shader->SetMat4("model", model);
  mesh->draw();
}
