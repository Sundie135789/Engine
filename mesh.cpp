
#include <GL/glew.h>
#include <GL/gl.h>
#include "headers/mesh.hpp"
Mesh::Mesh(std::vector<float> vertices,std::vector<unsigned int> indices , int verticeCount){
  this->indicesSize = indices.size(); 
  glGenBuffers(1, &vbo); 
  glGenBuffers(1, &ebo); // the ebo declaration thing
  glGenVertexArrays(1, &vao);
  
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER,sizeof(float)*vertices.size(), vertices.data(), GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), indices.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float),(void*)0);
  glEnableVertexAttribArray(0); 
  glBindVertexArray(0); 
  glBindBuffer(GL_ARRAY_BUFFER, 0); // safely unbind vbo
}
Mesh::~Mesh(){
  glDeleteVertexArrays(1, &vao);
  glDeleteBuffers(1, &vbo);
  glDeleteBuffers(1, &ebo);
}
void Mesh::Draw(){
  glBindVertexArray(vao);
  glDrawElements(GL_TRIANGLES, this->indicesSize, GL_UNSIGNED_INT, 0);
}
