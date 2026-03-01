#include "text.hpp"
#include "global.hpp"
#include <GL/glew.h>
#include <unordered_map>

GLuint textVAO = 0, textVBO = 0;
std::unordered_map<char, Character> fontCharacters;
unsigned int fontTextureID = 0;
int fontLineHeight = 0;
void initTextRender(){
  glGenVertexArrays(1, &textVAO);
  glGenBuffers(1, &textVBO);
  glBindVertexArray(textVAO);
  glBindBuffer(GL_ARRAY_BUFFER, textVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4,nullptr, GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4*sizeof(float), 0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

}
void renderText(Shader &shader, const std::string &text, float x, float y, float scale, float color[]){
  shader.use();
  glUniform3f(glGetUniformLocation(shader.shaderProgram, "textColor"), color[0], color[1], color[2]);
  glUniform1i(glGetUniformLocation(shader.shaderProgram, "text"), 0);
  glActiveTexture(GL_TEXTURE0);
  glBindVertexArray(textVAO);
  for(char c : text){
    if(fontCharacters.find(c) == fontCharacters.end()) continue;

    Character ch = fontCharacters[c];
    float xpos = x + ch.xOffset * scale;
    float ypos = y - (ch.height - ch.yOffset) * scale;
    float w = ch.width * scale;
    float h = ch.height * scale;
    float vertices[6][4] = {
      {xpos, ypos+h, ch.u0, ch.v1},
      {xpos, ypos, ch.u0, ch.v0},
      {xpos + w, ypos, ch.u1,ch.v0},
      {xpos, ypos+h, ch.u0, ch.v1},
      {xpos + w,ypos,ch.u1,ch.v0},
      {xpos + w, ypos + h, ch.u1, ch.v1}
    };
    glBindTexture(GL_TEXTURE_2D, fontTextureID);
    glBindBuffer(GL_ARRAY_BUFFER, textVBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glDrawArrays(GL_TRIANGLES,0,6);
    x += ch.xAdvance * scale;
  }
  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);
}
