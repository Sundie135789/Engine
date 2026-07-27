#include "headers/mesh.hpp"
#include "headers/log.hpp"
Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices){
  this->vertices = vertices;
  this->indices = indices;
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(), GL_STATIC_DRAW);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(),vertices.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  Log::Success("Mesh loaded: Vertex Count " + std::to_string(vertices.size()) + "\n");
}
void Mesh::Draw() const{
  glBindVertexArray(vao);
  //glDrawArrays(GL_TRIANGLES, 0, vertices.size());
  glDrawElements(GL_TRIANGLES, 0, GL_UNSIGNED_INT, 0);
}
