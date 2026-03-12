/*
 he model matrix is handled by a Gameobject's Transform class
 The projection and view matrices require a separate Camera class, even if there
 is only one Camera (uptill now). This is because the code inside a Camera
 class, written raw inside the main function in main.cpp would be catastrophic
 for cleanliness;
 * */

/*
 The Font atlas is a PNG file containing all the characters of a font,
 tightly-packed together. We load a font atlas from CPU side to the GPU as
 GL_TEXTURE_2D. Whenever we need a character for rendering, we can look at the
 fnt data, look at the atlas, and get the character. This is how bitmap font
 texture atlas system works.
 * */
/*
 *+------------------------------------------------+
|                                                |
|              OpenGL Viewport                   |
|                                                |
+------------------------------------------------+
| > spawn cube 0 0 0                             |  ← full width
| > set cube.scale 2                             |     scrollable history
| > _                                            |     above input line
+------------------------------------------------+
 * */
// TODO: refactor side pane -> implement ImGui.
// TODO: https://character.ai/chat/SeebJuz_llkYvFhSUGdWhuUEh2TtciQIBIdbLpkWDs4
//  TODO: start from nvim-treesitter.
//  https://claude.ai/chat/0a3c8bd0-fd49-4a5c-b0e9-6f6610c10009
// TODO: -->
// !-->
#include "assets/imgui.h"
#include "assets/imgui_impl_glfw.h"
#include "assets/imgui_impl_opengl3.h"
#include "assets/imgui_stdlib.h"
#include "headers/camera.hpp"
#include "headers/gameobject.hpp"
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
std::vector<GameObject *> gameobjects;
std::string commandBuffer = "";
bool commandEnabled = false;
void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mods) {
  /*std::cout << "VALUE OF COMMAND ENABLED: " << std::to_string(commandEnabled)
   * << std::endl;*/
  ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
  if (action != GLFW_PRESS)
    return;
  if (key >= GLFW_KEY_A && key <= GLFW_KEY_Z) {
    char c = 'a' + (key - GLFW_KEY_A);
    if (commandEnabled)
      commandBuffer += c;
  } else if (key == GLFW_KEY_SPACE) {
    if (commandEnabled)
      commandBuffer += " ";
  } else if (key == GLFW_KEY_ENTER) {
    if (commandEnabled) {
      run_command(commandBuffer);
      commandBuffer = "";
    }
  } else if (key == GLFW_KEY_BACKSPACE) {
    if (commandEnabled && commandBuffer != "") {
      commandBuffer.pop_back();
    }
  } else if (key == GLFW_KEY_MINUS) {
    commandEnabled = !commandEnabled;
  }
}
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
  glfwSetKeyCallback(window, key_callback);
  glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
  // --- OpenGL Code ---
  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  io.IniFilename = nullptr;
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
  // Setup Platform/Renderer backends
  ImGui_ImplGlfw_InitForOpenGL(
      window, false); // Second param install_callback=true will install GLFW
                      // callbacks and chain to existing ones.
  ImGui_ImplOpenGL3_Init();
  ImGui::StyleColorsDark();

  // Loading Font
  io.FontDefault =
      io.Fonts->AddFontFromFileTTF("assets/IosevkaCustom-Regular.ttf", 22.0f);
  ImGuiStyle &style = ImGui::GetStyle();
  style.FrameRounding = 4.0f;
  style.WindowRounding = 6.0f;
  Camera *mainCamera = new Camera((float)WINDOW_WIDTH / WINDOW_HEIGHT);
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

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    assert(mainCamera != nullptr);

    for (GameObject *g : gameobjects) {
      g->draw(*mainCamera);
    }

    if (commandEnabled) {
      ImGui::SetNextWindowPos(ImVec2(0, 1020), ImGuiCond_FirstUseEver);
      ImGui::SetNextWindowSize(ImVec2(WINDOW_WIDTH, 300),
                               ImGuiCond_FirstUseEver);
      ImGui::Begin("Terminal");
      ImGui::InputText("Command : ", &commandBuffer);
      ImGui::End();
      /* glUseProgram(sidePaneShaderProgram);
       glBindVertexArray(sidePaneVAO);
       glUniform3f(glGetUniformLocation(sidePaneShaderProgram, "uColor"),
       0.133f, 0.133f, 0.133f); glDisable(GL_DEPTH_TEST);
       glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
       glBindVertexArray(0);
       glDisable(GL_DEPTH_TEST);
       if (commandBuffer == "") renderText(*textShader, "Enter Command Here...",
       1012.5f, WINDOW_HEIGHT - 75.0f, 1.0f, command_default_color); else
       renderText(*textShader, commandBuffer, 1012.5f,
       WINDOW_HEIGHT-75.0f, 1.0f, command_color); glLineWidth(3.0f);
       glBindVertexArray(commandFieldVAO);
       glUseProgram(commandFieldShader->shaderProgram);
       glDrawArrays(GL_LINE_LOOP, 0, 4);
       glEnable(GL_DEPTH_TEST);
       //separator line
       separatorader->use();
       glBindVertexArray(separatorVAO);
       glDrawArrays(GL_LINES, 0, 2);
       glBindVertexArray(0);*/
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
