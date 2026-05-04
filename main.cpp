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
#include "headers/material.hpp"
#include "stb_image.h"
#include <GL/gl.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#include <vector>
#define WINDOW_WIDTH 2560
#define WINDOW_HEIGHT 1920
//Todo priority list below.
//TODO: Focus on creating top bar, File->Create Object->Cube,Square,Triangle,etc., Quit button. all using ImGui.
//TODO: Focus on Vertex class, replace mesh.cpp fragile stride and byteOffset with a Vertex struct. consisting of glm::vec3s. 
//TODO: focus on sundiecube and GUI later, first do material class and make sure code compiles. material contains a Mesh and Shader pointer.
//TODO: parse sundiecube.sundie, update github README.md to tell the downloader that we have to first run a specific script for blender support./
Camera* mainCamera;
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
  GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT,"GameEngine - SundieCoder v1.0", nullptr, nullptr);
  glfwMakeContextCurrent(window);
  glewExperimental = GL_TRUE;
  GLenum glewStatus = glewInit();
  if (glewStatus != GLEW_OK) {
    std::cout << "GLEW Init error" << std::endl;
    goTerminate();
    return 1;
  }
  glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
  // Setup Dear ImGui context
  ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.FontGlobalScale = 1.5f;
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();
	// Engine code
	// 	Vertex data (3 floats) -> Normals data (3 floats) -> RGB data (optional 3 floats) -> UV data (optional 2 floats)

	mainCamera = new Camera((float)WINDOW_WIDTH/(float)WINDOW_HEIGHT);
  /*std::vector<float> vertices = {-0.375f, -0.375f, 0.0f,0.0f, 0.0f, 1.0f, 0.0f, 0.0f,// given: vertices, normals, UV
                      					 0.375f,  -0.375f, 0.0f,0.0f, 0.0f, 1.0f, 1.0f, 0.0f,// no color along with texture.
                      					 0.0f,    0.375f,  0.0f,0.0f, 0.0f, 1.0f, 0.5f, 1.0f};*/
	//     Mesh(std::vector<float> vertices, int verticeCount, int stride);
	std::vector<float> vertices = {
		-0.375f, -0.375f, 0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 0.5f, 0.5f,
		0.375f, -0.375f, 0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 0.5f, 0.5f,
		0.0f, 0.375f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f
	};
 // Texture *texture = new Texture	("assets/monkey.png");
  Mesh *mesh = new Mesh(vertices, 3, 9);
  Mesh *mesh2 = new Mesh(vertices, 3, 9);
  Shader *shader = new Shader("shaders/plain.vert", "shaders/plain.frag");
  Transform *transform = new Transform();
  Transform *transform2 = new Transform();
	transform2->position[0] += 1.0f;
	Material *material = new Material(shader, mesh);
	Material *material2 = new Material(shader, mesh2);
	GameObject* gameobject = new GameObject("triangle");
  gameobject->SetMaterial(material);
  gameobject->SetTransform(transform);
  gameobjects.push_back(gameobject);
	GameObject* gameobject2 = new GameObject("second triangle");
	gameobject2->SetMaterial(material2);
	gameobject2->SetTransform(transform2);
	gameobjects.push_back(gameobject2);
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
		/*mainCamera->position[0] = glm::clamp(mainCamera->position[0], -5.0f, 5.0f);
		mainCamera->position[2] = glm::clamp(mainCamera->position[2], 0.5f, 3.0f);*/
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
		assert(g !=nullptr);
      g->draw(*mainCamera);
			if(g->menuOpen){
				g->toggleObjectMenu();
			}
    }
		if(ImGui::BeginMainMenuBar()){
			if(ImGui::BeginMenu("File")){
				if(ImGui::MenuItem("Open", "Ctrl+O")) {}
				if(ImGui::MenuItem("Save", "Ctrl+S")) {}
				ImGui::EndMenu();
			}
			if(ImGui::BeginMenu("Edit")){
				if(ImGui::MenuItem("Undo", "Ctrl+Z")){}
					ImGui::EndMenu();	
			}
			ImGui::EndMainMenuBar();
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
