#pragma once
#include "shader.hpp"
void loadSidePane();
void loadCommandField();
extern GLuint sidePaneShaderProgram;
extern GLuint sidePaneVAO;
extern GLuint commandFieldVAO;
extern Shader* commandFieldShader;

