#include "GL/glew.h"
#include "headers/globals.hpp"
#include "headers/log.hpp"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "headers/window.hpp"
#include "headers/serialize.hpp"
void framebuffer_size_callback(GLFWwindow* window, int width, int height ){
  if(width == 0 || height == 0) return;
  glViewport(0, 0, width, height);
  editorCamera->aspect = (float)width / (float)height;
  gameCamera->aspect = (float)width / (float)height;
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
  if(action == GLFW_PRESS){
    if(key == GLFW_KEY_F3){
      if(g_EngineState == EngineState::Editing){
        g_editorTransforms.clear();
        g_editorTransforms.shrink_to_fit();
        for(auto& go : gameobjects){
          g_editorTransforms.push_back(go->transform);
        }
        g_EngineState = EngineState::Playing;
      }else{
        for(int i=0; i<gameobjects.size();i++){
          gameobjects.at(i)->transform = g_editorTransforms.at(i);
        }
        g_EngineState = EngineState::Editing;
      }
    }
    if(key == GLFW_KEY_T){
      currentGizmoOp = ImGuizmo::TRANSLATE;
    }
    if(key == GLFW_KEY_S){
      currentGizmoOp = ImGuizmo::SCALE;
    }
    if(key == GLFW_KEY_R){
      currentGizmoOp = ImGuizmo::ROTATE;
    }
    if(key == GLFW_KEY_P){
      editorCamera->projectionType = 
        editorCamera->projectionType == ProjectionType::Perspective ? ProjectionType::Orthographic : ProjectionType::Perspective;
    }
  }
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
  yoffset == 1 ? editorCamera->ZoomIn() : editorCamera->ZoomOut();
}
void Window::setCursorMode(int mode){
  glfwSetInputMode(window, GLFW_CURSOR, mode);
  cursorMode = mode;
}
Window::Window(int width, int height, std::string title){
  glfwInit();
  window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
  if(!window){
    Log::Fatal("Failed to create GLFW window\n");
    Serialize::ExitEngine(1);
  }
  glewExperimental = GL_TRUE;
  glfwMakeContextCurrent(window);
  SetVerticalSync(this->GetWindowHandle());
  glewInit();
  glDisable(GL_CULL_FACE);
  glFrontFace(GL_CCW);
  glCullFace(GL_BACK);
  setCursorMode(GLFW_CURSOR_NORMAL);
  glEnable(GL_DEPTH_TEST);
  glViewport(0,0,width, height);
  glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
  glfwSetKeyCallback(window, key_callback);
  glfwSetScrollCallback(window, scroll_callback);
  Log::Success("GLFWwindow created successfully!\n");
}
int Window::GetMouseButton(int button){
  return glfwGetMouseButton(window, button);
}
void Window::SetVerticalSync(GLFWwindow* window){
  glfwMakeContextCurrent(window);
  glfwSwapInterval(settings.graphics.vsync ? 1 : 0);
}
void Window::PollEvents(){
  glfwPollEvents();
}
void Window::setTitle(std::string title){
  glfwSetWindowTitle(GetWindowHandle(), title.c_str());
}
int Window::GetCursorMode(){
  return cursorMode;
}
void Window::SwapBuffers(){
  if(window){
    glfwSwapBuffers(window);
    return;
  }
  Log::Fatal("Window found null in Window::SwapBuffers\n");
  Serialize::ExitEngine(1);
}
bool Window::ShouldClose(){
  if(window){
    return glfwWindowShouldClose(window);
  }
  Log::Fatal("Window found null in Window::ShouldClose\n");
  Serialize::ExitEngine(1);
  return true;
}
int Window::GetKey(int key){
  if(window){
    return glfwGetKey(this->window, key);
  }
  Log::Fatal("Window found null in Window::GetKey\n");
  Serialize::ExitEngine(1);
  return -1;
}

void Window::GetCursorPos(double& xPos, double& yPos){
  if(window){
    return glfwGetCursorPos(this->window, &xPos, &yPos);
  }
  Log::Fatal("Window found null in Window::GetCursorPos\n");
  Serialize::ExitEngine(1);
}

GLFWwindow* Window::GetWindowHandle(){
  if(window){
    return window;
  }
  Log::Fatal("Window found null in WIndow::GetWindowHandle\n");
  Serialize::ExitEngine(1);
  return nullptr;
}
float Window::GetTime(){
  return glfwGetTime();
}
void Window::Terminate(){
  glfwTerminate();
}
// TODO window resize detect, gl view port
                                                             
