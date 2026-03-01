#pragma once
#include <string>
#include "shader.hpp"
#include "character.hpp"
void initTextRender();
void renderText(Shader &shader, const std::string &text, float x, float y, float scale, float color[]);
