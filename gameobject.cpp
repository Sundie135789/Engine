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
	memset(XBuffer, 0, sizeof(XBuffer));
	XBuffer[0] = '\0';
	memset(YBuffer, 0, sizeof(YBuffer));
	YBuffer[0] = '\0';
	memset(ZBuffer, 0, sizeof(ZBuffer));
	ZBuffer[0] = '\0';
}
void GameObject::toggleObjectMenu(){
	const char* objectName = this->name.c_str();
	ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowPos(ImVec2(1800, 0), ImGuiCond_FirstUseEver);
	ImGui::Begin(objectName);
	ImGui::SetWindowFontScale(1.5f);
	ImGui::Text("Transform");
	if(ImGui::InputText("Pos X",this->XBuffer, IM_ARRAYSIZE(XBuffer))){}
	if(ImGui::InputText("Pos Y",this->YBuffer, IM_ARRAYSIZE(YBuffer))){}
	if(ImGui:: InputText("Pos Z",this->ZBuffer, IM_ARRAYSIZE(ZBuffer))){}
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
  shader->SetMatrix("view", camera.GetViewMatrix());
  shader->SetMatrix("projection", camera.GetProjectionMatrix());
  glm::mat4 model = transform->GetModelMatrix();
  shader->SetMatrix("model", model);
  mesh->draw();
}
