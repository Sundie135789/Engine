#include "headers/ui.hpp"
#include <GLFW/glfw3.h>
#include <cstdio>
#include "headers/input.hpp"
#include "headers/serialize.hpp"
#include "headers/globals.hpp"
#include "vendor/imgui/imgui.h"
#include "vendor/imgui/backends/imgui_impl_glfw.h"
#include "vendor/imgui/backends/imgui_impl_opengl3.h"
#include "vendor/pfd/portable-file-dialogs.h"
#include "vendor/imguizmo/ImGuizmo.h"
#include <glm/gtc/type_ptr.hpp>
#include <filesystem>
#include <string>
namespace fs = std::filesystem;

static char worldName[128] = "", objRename[128], textureSet[128];
static bool openSavePopup = false, openLoadPopup = false, openLoadErrorPopup = false, openEmptyRenamePopup = false
, showInputManager = false, showSettings = false, openInvalidKeybindPopup = false;
bool UI::triggerFilePick = false;
bool UI::triggerModelPick = false;
static std::string errorMsg = "";
void UI::DrawTransformGizmo(Gameobject* gameobject, const glm::mat4& view, const glm::mat4& proj){
  if(!gameobject) return;
  ImGuizmo::SetDrawlist(ImGui::GetForegroundDrawList());
  ImGuizmo::AllowAxisFlip(false);
  ImGuizmo::GetStyle().TranslationLineThickness = 7.0f;
  ImGuizmo::GetStyle().TranslationLineArrowSize = 14.0f;
  ImGuizmo::GetStyle().RotationLineThickness = 6.0f;
  ImGuizmo::GetStyle().ScaleLineThickness = 6.0f;
  ImGuiViewport* viewport = ImGui::GetMainViewport();
  ImGuizmo::SetRect(viewport->Pos.x, viewport->Pos.y, viewport->Size.x, viewport->Size.y);
  glm::mat4 modelMatrix = gameobject->getModelMatrix();
  ImGuizmo::Manipulate(
      glm::value_ptr((view)),
      glm::value_ptr((proj)),
      ImGuizmo::TRANSLATE,
      ImGuizmo::LOCAL,
      glm::value_ptr(modelMatrix)
      );
    if(ImGuizmo::IsUsing()){
      gameobject->setModelMatrix(modelMatrix);
    }
}
void UI::SaveAndExit(){
  if(strcmp(worldName, "")) 
    Serialize::SaveWorld("worlds/" + std::string(worldName)+ ".json");
}
std::string UI::OpenModelpicker(){
  auto selection = pfd::open_file("Import Model", "", 
      {"Autodesk FBX (*.fbx)", "*.fbx"}).result();
  if(selection.empty())
    return "";
  return selection[0];
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
      //DrawTransformGizmo(gameobjects[i].get(), editorCamera->GetViewMatrix(), editorCamera->GetProjectionMatrix());
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
  ImGui::Text("Material Properties"); ImGui::SetNextItemWidth(400.0f);

  ImGui::ColorEdit3("Albedo Color", &obj->material.albedoValue.x);
  if(ImGui::Button("Import Albedo Map", ImVec2(200.0f, 40.0f))){
    obj->material.setAlbedoPath(UI::OpenFilepicker());
  }

  ImGui::SetNextItemWidth(300.0f);
  ImGui::SliderFloat("Roughness", &obj->material.roughnessValue, 0.0f, 1.0f, "%.3f");
if(ImGui::Button("Import Roughness Map", ImVec2(250.0f, 40.0f))){
    obj->material.setAlbedoPath(UI::OpenFilepicker());
  }
  ImGui::SetNextItemWidth(300.0f);

  ImGui::SliderFloat("Metallic", &obj->material.metallicValue , 0.0f, 1.0f, "%.3f");
if(ImGui::Button("Import Metallic Map", ImVec2(250.0f, 40.0f))){
    obj->material.setMetallicPath(UI::OpenFilepicker());
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
  ImGuiIO& io = ImGui::GetIO();
  std::string fontPath;
  const char* homeDir = std::getenv("HOME");
  if(homeDir != nullptr){
    fontPath = std::string(homeDir) + "/.local/share/fonts/JetBrainsMonoNerdFont-Regular.ttf";
  }
  ImFontConfig font_cfg;
  font_cfg.OversampleH = 3;
  font_cfg.OversampleV = 3;
  font_cfg.PixelSnapH = true;

  ImFont* engineFont = nullptr;
  if(!fontPath.empty() && fs::exists(fontPath)){
    engineFont = io.Fonts->AddFontFromFileTTF(fontPath.c_str(), 25.0f, &font_cfg);
  }
  if(engineFont == nullptr){
    io.Fonts->AddFontDefault();
  }
  ImGui::StyleColorsDark();
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 330");
  io.Fonts->Build();
}
void UI::Menubar(){

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
      if(ImGui::MenuItem("Import Model (FBX)")){
        triggerModelPick = true;
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
      ImGui::EndMenu();
    }
    
    if(ImGui::BeginMenu("Input")){
      if(ImGui::MenuItem("Open Input Manager")){
        showInputManager = true;
      }
      ImGui::EndMenu();
    }
    
      if(ImGui::BeginMenu("Open Settings")){
        showSettings = true;
      ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
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
    if(ImGui::Button("Cancel")){
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
          openLoadErrorPopup = true;
        }else{
          Serialize::LoadWorld(path);
        }
      }
      ImGui::CloseCurrentPopup();
    }
    ImGui::SameLine();
    if(ImGui::Button("Cancel")){
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

  if(showInputManager){
    ImGui::SetNextWindowSize(ImVec2(1300, 800), ImGuiCond_FirstUseEver);
    if(ImGui::Begin("Input Manager", &showInputManager)){
      if(ImGui::BeginTable("KeybindsTable", 2, ImGuiTableFlags_Resizable | ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)){
        ImGui::TableSetupColumn("Action", ImGuiTableColumnFlags_WidthStretch, 0.6f);
        ImGui::TableSetupColumn("Key Assigned", ImGuiTableColumnFlags_WidthStretch, 0.4f);
        ImGui::TableHeadersRow();
        for(size_t i = 0; i < Input::gameKeybinds->size(); i++){
          Input::Keybind& keybind = Input::gameKeybinds->at(i);
          ImGui::TableNextRow();
          ImGui::TableNextColumn();
          ImGui::Text("%s",keybind.actionName.c_str());
          ImGui::TableNextColumn();
          char buf[32];
          if(keybind.assignedKey == ImGuiKey_None){
            strcpy(buf, "None");
          }else{
            const char* keyName = ImGui::GetKeyName(keybind.assignedKey);
            snprintf(buf, sizeof(buf), "%s", keyName ? keyName : "None");
          }
          ImGui::PushID(static_cast<int>(i));
          if(ImGui::Button(buf, ImVec2(-FLT_MIN, 0.0f))){
            //TODO
            keybind.waitingForInput = true;
          }
          if(keybind.waitingForInput){
            for(int key = ImGuiKey_NamedKey_BEGIN; key < ImGuiKey_NamedKey_END; key++){
              if(ImGui::IsKeyPressed((ImGuiKey)key)){
                keybind.assignedKey = (ImGuiKey)key;
                keybind.waitingForInput = false;
                break;
              }
            }
            ImGui::Text("Press any key...");
          }
          ImGui::PopID();
        }
        ImGui::EndTable();
      }
    }
    ImGui::End();
  }

  if(showSettings){
    /*ImGui::SetNextWindowSize(ImVec2(1400, 900), ImGuiCond_FirstUseEver);
    if(ImGui::Begin("Settings", &showSettings)){
      ImGui::Text("Graphics Settings");
      if(ImGui::Checkbox("V-Sync", &vsync)){
        mainWindow->SetVerticalSync();
      }
      ImGui::Text("Controls");
      ImGui::SliderFloat("Movement speed", &camera_speed, 1.0f, 20.0f, "%.1f m/s");
      ImGui::SliderFloat("Camera sensitivity", &sensitivity, 0.05f, 0.25f, "%.2f");
      ImGui::End();
    }*/
    ImGui::SetNextWindowSize(ImVec2(1400, 900), ImGuiCond_FirstUseEver);
    if(ImGui::Begin("Settings", &showSettings)){
    ImGui::BeginChild("Sidebar", ImVec2(150, 0), true);
    static int select = 0;
    if(ImGui::Selectable("Graphics", select == 0))
      select = 0;
    if(ImGui::Selectable("Controls", select == 1))
      select = 1;
    ImGui::EndChild();
    ImGui::SameLine();
    ImGui::BeginChild("Content", ImVec2(0, 0), true);
    if(select == 0)
    {
      ImGui::Text("Graphics settings");
      ImGui::Separator();
      if(ImGui::Checkbox("Chromatic Abberation", &settings.graphics.chromaticAbberation)){
        // TODO
      }
      if(ImGui::Checkbox("V-Sync", &settings.graphics.vsync)){
        mainWindow->SetVerticalSync(mainWindow->GetWindowHandle());
      }
    }
    if(select == 1)
    {
      ImGui::Text("Controls");
      ImGui::Separator();
      ImGui::PushItemWidth(500.0f)  ;
      ImGui::SliderFloat("Mouse Sensitivity", &settings.controls.sensitivity, 0.05f, 0.25f, "%.2f");
      ImGui::PopItemWidth();
      ImGui::SliderFloat("Editor Camera Speed", &settings.controls.camera_speed, 1.0f, 10.0f, "%.1f");
    }
    ImGui::EndChild();
    ImGui::End();
    }
  }
}

