#include "mesh.hpp"
Mesh::Mesh(float* vertices, int verticeCount, bool hasTexCoords){
  int floatsPerVertice = (hasTexCoords) ? 5 : 3; 
  GLuint stride = (hasTexCoords) ? floatsPerVertice * sizeof(float) : floatsPerVertice * sizeof(float);
  this->vertices = vertices;
  this->verticeCount = verticeCount;
  glGenBuffers(1,  &vbo);
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, floatsPerVertice * verticeCount * sizeof(float), vertices, GL_DYNAMIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
  glEnableVertexAttribArray(0);
  if(hasTexCoords){
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
  }
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}
Mesh::~Mesh(){
  glDeleteBuffers(1, &this->vbo);
  glDeleteVertexArrays(1, &this->vao);
}
void Mesh::draw(){
  
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER,vbo);
  if(verticeCount == 3){
    shape = GL_TRIANGLES;
  }else{
    shape = GL_TRIANGLE_FAN;
  }
  glDrawArrays(shape, 0, verticeCount);
}
