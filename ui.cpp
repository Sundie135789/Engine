#include "headers/ui.hpp"
#include <GLFW/glfw3.h>
#include <cstdio>
#include <iostream>
#include "headers/input.hpp"
#include "headers/assetmanager.hpp"
#include "headers/serialize.hpp"
#include "headers/globals.hpp"
#include "vendor/imgui/imgui.h"
#include "vendor/imgui/backends/imgui_impl_glfw.h"
#include "vendor/imgui/backends/imgui_impl_opengl3.h"
#include "vendor/pfd/portable-file-dialogs.h"
#include <filesystem>
#include <string>
namespace fs = std::filesystem;

static char worldName[128] = "", objRename[128], textureSet[128];
static bool openSavePopup = false, openLoadPopup = false, openLoadErrorPopup = false, openEmptyRenamePopup = false;
bool UI::triggerFilePick = false;
static std::string errorMsg = "";
void UI::SaveAndExit(){
  if(strcmp(worldName, "")) 
    Serialize::SaveWorld("worlds/" + std::string(worldName)+ ".json");
}
std::string UI::OpenFilepicker(){
  auto selection = pfd::open_file("Set Texture", "", {"Image Files", "*.png *.jpg *.jpeg *.bmp *.hdr *.pic"}).result();
  if(selection.empty())
    return "assets/textures/missing_texture.png";
  return selection[0];
}
void UI::Hierarchy(){
  
  ImGui::SetNextWindowPos(ImVec2(0, 30), ImGuiCond_Always);
  ImGui::SetNextWindowSize(ImVec2(400, 1900), ImGuiCond_Always);
  ImGui::Begin("Hierarchy", nullptr, ImGuiWindowFlags_NoResize);
  for(int i=0;i<gameobjects.size();i++){
    if(ImGui::Selectable(gameobjects[i]->name.c_str())){
      selected = i;
    }
  }
  if(selected != -1){
    if(ImGui::IsKeyPressed(ImGuiKey_Delete) || ImGui::IsKeyPressed(ImGuiKey_Backspace)){
      if(!ImGui::GetIO().WantCaptureKeyboard){
        gameobjects.erase(gameobjects.begin() + selected);
        selected = -1;
      }
    }
    if(ImGui::IsKeyPressed(ImGuiKey_F2)){
      ImGui::OpenPopup("rename_popup");
    }
    if(ImGui::BeginPopup("rename_popup")){
      ImGui::Text("Enter new name");
      ImGui::SetKeyboardFocusHere();
      if(ImGui::InputText("###name", objRename, 128, ImGuiInputTextFlags_EnterReturnsTrue)){
        if(objRename[0] != '\0'){
          gameobjects[selected]->name = std::string(objRename);
          ImGui::CloseCurrentPopup();
          openEmptyRenamePopup = false;
        }else {
          openEmptyRenamePopup = true;
        }
      }
      if(openEmptyRenamePopup){
        ImGui::TextColored(ImVec4(1,0,0,1), "Name cannot be empty!");
      }
      ImGui::EndPopup();
    }
  }
  ImGui::End();
  }
void UI::LoadInspector() {
  ImGui::SetNextWindowPos(ImVec2(1900, 0), ImGuiCond_Always);
  ImGui::SetNextWindowSize(ImVec2(1200, 1900), ImGuiCond_Always); 
  ImGui::Begin("Properties", nullptr, ImGuiWindowFlags_NoResize);
  /*if(!gameobjects[selected]){
    std::cerr << "load inspector, gameobjects[selected] is null";
    std::exit(1);
  }*/
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
  //std::string currentTexture = "Current Texture: " + obj->material.texture->path;
  //ImGui::Text(currentTexture.c_str());
  ImGui::SetNextItemWidth(400.0f);
  
  /*if(ImGui::BeginCombo("Available Textures", obj->material.texture->path.substr(7).c_str())){
    for(int i=0;i<textures.size();i++){
      std::string textureName = textures[i];
      bool isSelected = (obj->material.texture->path == textureName);
      std::cout << "GAMEOBJECT TEXTURE: " << obj->material.texture->path << "\nTextureName: " << textureName << '\n'; 
      if(ImGui::Selectable(textureName.c_str(), isSelected)){
        obj->material.texture = AssetManager::GetTexture(textureName);
      }
    }
    ImGui::EndCombo();
  }*/
  if(ImGui::Button("Import Texture", ImVec2(300, 50))){
    UI::triggerFilePick = true;
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
  bool shouldCloseMenu = false;
  if(ImGui::BeginMainMenuBar()){
    if(ImGui::BeginMenu("File")){
      if(ImGui::MenuItem("Save World")){
        strcpy(worldName, "");
        openSavePopup = true;
      }
      if(ImGui::MenuItem("Load World")){
        strcpy(worldName, "");
        openLoadPopup = true;
      }
      ImGui::EndMenu();
    }
    if(openSavePopup){
      ImGui::OpenPopup("Save World Popup");
      openSavePopup = false;
    }
    if(openLoadPopup){
      ImGui::OpenPopup("Load World Popup");
      openLoadPopup = false;
    }
    if(openLoadErrorPopup){
      ImGui::OpenPopup("Error Popup");
      openLoadErrorPopup = false;
    }
    if(ImGui::BeginPopupModal("Save World Popup", NULL, ImGuiWindowFlags_AlwaysAutoResize)){
      ImGui::Text("Enter world name:");
      ImGui::InputText("###saveworld", worldName, IM_ARRAYSIZE(worldName));
      if(ImGui::Button("Save")){
        if(strlen(worldName) > 0){
          std::string path = std::string("worlds/") + worldName + ".json";
          Serialize::SaveWorld(path);
        }
          ImGui::CloseCurrentPopup();
      }
      ImGui::SameLine();
      if(ImGui::Button( "Cancel")){
        ImGui::CloseCurrentPopup();
      }
      ImGui::EndPopup();
    }
      if(ImGui::BeginPopupModal("Load World Popup", NULL, ImGuiWindowFlags_AlwaysAutoResize)){
      ImGui::Text("Enter world name:");
      ImGui::InputText("###loadworld", worldName, IM_ARRAYSIZE(worldName));
      if(ImGui::Button("Load")){
        if(strlen(worldName) > 0){
          std::string path = std::string("worlds/") + worldName + ".json";
          if(!fs::exists(path)){
            errorMsg = "File not found!";
            openLoadErrorPopup= true;
          }else{
            Serialize::LoadWorld(path);
          }
        }
          ImGui::CloseCurrentPopup();
      }
      ImGui::SameLine();
      if(ImGui::Button( "Cancel")){
        ImGui::CloseCurrentPopup();
      }
      ImGui::EndPopup();
    }
    if(ImGui::BeginPopupModal("Error Popup", NULL, ImGuiWindowFlags_AlwaysAutoResize)){
      ImGui::Text("%s", errorMsg.c_str());
      if(ImGui::Button("OK")){
        ImGui::CloseCurrentPopup();
      }
      ImGui::EndPopup();
    }
    if(ImGui::BeginMenu("GameObject")){
      if(ImGui::MenuItem("Create Cube")){
        Gameobject::CreateCube();
      }
      if(ImGui::MenuItem("Create Plane")){
        Gameobject::CreatePlane();
      }
      //if(ImGui::MenuItem("Create Point Light")){
        //TODO
      //}
      ImGui::EndMenu();
    }
    if(ImGui::BeginMenu("Input")){
      if(ImGui::MenuItem("Standard WASD + Mouse")){
        Input::standardWASDMouse = true;
      }
      ImGui::EndMenu();
    }
    if(ImGui::BeginMenu("Settings")){
      /*if(ImGui::Checkbox("V-Sync", &vsync)){
        mainWindow->SetVerticalSync();
      }
      ImGui::Text("Controls");
      ImGui::SliderFloat("Movement speed", &camera_speed, 1.0f, 20.0f, "%.1f m/s");
      ImGui::SliderFloat("Camera sensitivity", &sensitivity, 0.05f, 0.25f, "%.2f");
      */
      ImGui::SetNextWindowSize(ImVec2(1400, 900));
      if(ImGui::Begin("Settings")){
        ImGui::Text("Graphics Settings");
        if(ImGui::Checkbox("V-Sync", &vsync)){
          mainWindow->SetVerticalSync();
        }
        ImGui::Text("Controls");
        ImGui::SliderFloat("Movement speed", &camera_speed, 1.0f, 20.0f, "%.1f m/s");
        ImGui::SliderFloat("Camera sensitivity", &sensitivity, 0.05f, 0.25f, "%.2f");
        ImGui::End();
      }
      ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
  }
}
