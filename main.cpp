#include "assets/imgui.h"
#include "assets/imgui_impl_glfw.h"
#include "assets/imgui_impl_opengl3.h"
#include "assets/imgui_stdlib.h"
#include "headers/camera.hpp"
#include "headers/gameobject.hpp"
#include "headers/import.hpp"
#include "headers/global.hpp"
#include "headers/lang.hpp"
#include "headers/mesh.hpp"
#include "headers/shader.hpp"
#include "headers/texture.hpp"
#include "headers/transform.hpp"
#include "stb_image.h"
#include <GL/gl.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#define WINDOW_WIDTH 2560
#define WINDOW_HEIGHT 1920
// implement moving forward (change camera position) on W.
//
  Camera *mainCamera = new Camera((float)WINDOW_WIDTH / WINDOW_HEIGHT);
std::vector<GameObject *> gameobjects;
bool lastMouseButtonState = false;
double mouseX, mouseY;
float Zspeed = 0.01f;
float Xspeed = 0.01f;
/*void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
	
	if(action == GLFW_KEY_PRESS){
		if(key == GLFW_KEY_W){
			mainCamera->position[2] -= Zspeed;
		}else if(key == GLFW_KEY_S){
			mainCamera->position[2] += Zspeed;
		}
	}
}*/

void goTerminate() {
  for (auto g : gameobjects) {
    delete g;
  }
  gameobjects.clear();
  glfwTerminate();
}
int main(void) {
  if (!glfwInit()) {
    std::cout << "GLFW Init error" << std::endl;
    goTerminate();
    return 1;
  }
  GLFWwindow *window =
      glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT,
                       "GameEngine - SundieCoder v1.0", nullptr, nullptr);
  glfwMakeContextCurrent(window);
  glewExperimental = GL_TRUE;
  GLenum glewStatus = glewInit();
  if (glewStatus != GLEW_OK) {
    std::cout << "GLEW Init error" << std::endl;
    goTerminate();
    return 1;
  }
  glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
  // --- OpenGL Code ---
  // Setup Dear ImGui context
  ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();
  float vertices[] = {-0.375f, -0.375f, 0.0f, 0.0f, 0.0f,
                      0.375f,  -0.375f, 0.0f, 1.0f, 0.0f,
                      0.0f,    0.375f,  0.0f, 0.5f, 1.0f};
  Texture *texture = new Texture("assets/monkey.png");
  Mesh *mesh = new Mesh(vertices, 3, true);
  Shader *shader = new Shader("shaders/texture.vert", "shaders/texture.frag");
  Transform *transform = new Transform();
  shader->SetTexture(texture);
  GameObject *gameobject = new GameObject("triangle");
  gameobject->SetShader(shader);
  gameobject->SetMesh(mesh);
  gameobject->SetTransform(transform);
  gameobjects.push_back(gameobject);
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
		ImGuiIO& io = ImGui::GetIO();
		bool currentMouseButtonState=  glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
		if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
			mainCamera->position[2] -= Zspeed;
		}if(glfwGetKey(window,GLFW_KEY_S) == GLFW_PRESS){
			mainCamera->position[2] += Zspeed;
		} if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
			mainCamera->position[0] -= Xspeed;
		}if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
			mainCamera->position[0] += Xspeed;
		}
		mainCamera->position[0] = glm::clamp(mainCamera->position[0], -5.0f, 5.0f);
		mainCamera->position[2] = glm::clamp(mainCamera->position[2], 0.5f, 3.0f);
		if(currentMouseButtonState && !lastMouseButtonState && !io.WantCaptureMouse){
			glfwGetCursorPos(window, &mouseX, &mouseY);
			if(mouseX < 1000){
				GameObject* g = gameobjects.at(0);
				g->menuOpen = !g->menuOpen;
			}
		}
		lastMouseButtonState = currentMouseButtonState;

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    assert(mainCamera != nullptr);
    for (GameObject *g : gameobjects) {
      g->draw(*mainCamera);
			if(g->menuOpen){
				g->toggleObjectMenu();
			}
    }
		
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(window);
  }
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
  glfwDestroyWindow(window);
  goTerminate();
  return 0;
}
