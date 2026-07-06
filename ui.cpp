#include "headers/ui.hpp"
#include "headers/globals.hpp"
#include <iostream>
#include "vendor/imgui/imgui.h"
#include "vendor/imgui/backends/imgui_impl_glfw.h"
#include "vendor/imgui/backends/imgui_impl_opengl3.h"
void UI::Hierarchy(){
  ImGui::SetNextWindowPos(ImVec2(0, 30), ImGuiCond_Always);
  ImGui::SetNextWindowSize(ImVec2(400, 1900), ImGuiCond_Always);
  ImGui::Begin("Hierarchy", nullptr, ImGuiWindowFlags_NoResize);
  for(int i=0;i<gameobjects.size();i++){
    if(ImGui::Selectable(gameobjects[i]->name.c_str())){
      selected = i;
    }
  }
  if(selected != -1 && (ImGui::IsKeyPressed(ImGuiKey_Delete) || ImGui::IsKeyPressed(ImGuiKey_Backspace))){
    if(!ImGui::GetIO().WantCaptureKeyboard){
      gameobjects.erase(gameobjects.begin() + selected);
      selected = -1;
    }
  }
  ImGui::End();
}
void UI::LoadInspector() {
  ImGui::SetNextWindowPos(ImVec2(1900, 0), ImGuiCond_Always);
  ImGui::SetNextWindowSize(ImVec2(1200, 1900), ImGuiCond_Always); 
  ImGui::Begin("Properties", nullptr, ImGuiWindowFlags_NoResize);

  auto& obj = gameobjects[selected];
  ImGui::Text("Name: %s", obj->name.c_str());
  ImGui::Separator();

  if (ImGui::BeginTable("TransformTable", 2, ImGuiTableFlags_SizingFixedFit)) {
    ImGui::TableSetupColumn("Label", ImGuiTableColumnFlags_WidthFixed, 100.0f);
    ImGui::TableSetupColumn("Inputs", ImGuiTableColumnFlags_WidthFixed, 400.0f); 

    ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(15.0f, 0.0f));

    auto drawRow = [](const char* label, const char* id, float* data) {
      ImGui::TableNextColumn(); ImGui::Text("%s", label);
      ImGui::TableNextColumn(); ImGui::SetNextItemWidth(400.0f);
      ImGui::InputFloat3(id, data, "%.2f");
    };

    drawRow("Position", "##Pos", &obj->transform.position.x);
    drawRow("Rotation", "##Rot", &obj->transform.rotation.x);
    drawRow("Scale",    "##Scl", &obj->transform.scale.x);

    ImGui::PopStyleVar();
    ImGui::EndTable();
  }
  ImGui::Separator();
  ImGui::SetNextItemWidth(400.0f);
  if(ImGui::BeginCombo("Available Textures", obj->material.texture->path.substr(7).c_str())){
    for(int i=0;i<textures.size();i++){
      std::string textureName = textures[i].substr(7);
      bool isSelected = (obj->material.texture->path == textures[i]);
      if(ImGui::Selectable(textureName.c_str(), isSelected)){
        obj->material.texture->LoadTexture(textures[i]);
      }
    }
    ImGui::EndCombo();
  }
  ImGui::Separator();
  ImGui::SetNextItemWidth(400.0f);
  if(ImGui::ColorEdit3("Color", &obj->material.color.x)){
  }
  ImGui::End();
}
void UI::BeginFrame(){
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}
void UI::EndFrame(){
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
void UI::Init(GLFWwindow* window){
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGui::GetIO().FontGlobalScale = 1.5f;

  ImGui::StyleColorsDark();
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 330");
}
void UI::Menubar(){
  if(ImGui::BeginMainMenuBar()){
    if(ImGui::BeginMenu("File")){
      if(ImGui::MenuItem("Save World")){
        
      }
      if(ImGui::MenuItem("Load World")){

      }
      ImGui::EndMenu();
    }
    if(ImGui::BeginMenu("GameObject")){
      if(ImGui::MenuItem("Create Cube")){
        Gameobject::CreateCube();
      }
      if(ImGui::MenuItem("Create Plane")){
        Gameobject::CreatePlane();
      }
      if(ImGui::MenuItem("Create Point Light")){
        //TODO
      }
      ImGui::EndMenu();
    }
    if(ImGui::BeginMenu("Settings")){
      if(ImGui::Checkbox("V-Sync", &vsync)){
        mainWindow->SetVerticalSync();
      }
      ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
  }
}
