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
void UI::LoadInspector(){
  ImGui::SetNextWindowPos(ImVec2(1900, 0), ImGuiCond_Always);
  ImGui::SetNextWindowSize(ImVec2(1200, 1900), ImGuiCond_Always); 
  ImGui::Begin("Properties", nullptr, ImGuiWindowFlags_NoResize);
  ImGui::Text("Name: %s", gameobjects[selected]->name.c_str());
  ImGui::Separator();

  if (ImGui::BeginTable("TransformTable", 2, ImGuiTableFlags_SizingFixedFit)) 
  {
    ImGui::TableSetupColumn("Label", ImGuiTableColumnFlags_WidthFixed, 100.0f);
    ImGui::TableSetupColumn("Inputs", ImGuiTableColumnFlags_WidthFixed, 400.0f); 

    ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(15.0f, 0.0f));

    // --- ROW 1: POSITION ---
    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::Text("Position");
    
    ImGui::TableSetColumnIndex(1);
    ImGui::SetNextItemWidth(400.0f); 
    ImGui::InputFloat3("##Pos", &gameobjects[selected]->transform->position.x, "%.2f");

    // --- ROW 2: ROTATION ---
    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::Text("Rotation");
    
    ImGui::TableSetColumnIndex(1);
    ImGui::SetNextItemWidth(400.0f);
    ImGui::InputFloat3("##Rot", &gameobjects[selected]->transform->rotation.x, "%.2f");

    // --- ROW 3: SCALE ---
    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::Text("Scale");
    
    ImGui::TableSetColumnIndex(1);
    ImGui::SetNextItemWidth(400.0f);
    ImGui::InputFloat3("##Scl", &gameobjects[selected]->transform->scale.x, "%.2f");

    ImGui::PopStyleVar();
    ImGui::EndTable();
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
      if(ImGui::MenuItem("Save Scene")){
        //TODO save scene
      }
      ImGui::EndMenu();
    }
    if(ImGui::BeginMenu("GameObject")){
      if(ImGui::MenuItem("Cube")){
        Gameobject::CreateCube();
      }
      if(ImGui::MenuItem("Plane")){
        Gameobject::CreatePlane();
      }
      ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
  }
}
