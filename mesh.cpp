#include "mesh.hpp"
#include <cassert>
#include <iostream>
#include <vector>
#include <stdbool.h>

#include <cstdlib>
/*
	Attribute order for each vertex declared as follows:
	Vertex data (3 floats) -> Normals data (3 floats) -> RGB data (optional 3 floats) -> UV data (optional 2 floats)
	Max stride of a vertex = 11 * sizeof(float);
	This is followed strictly.
	
*/
Mesh::Mesh(std::vector<float> vertices, int verticeCount, int stride){
	/*
		-0.5f, -0.5f, 0.0f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
		0.5f, -0.5f, 0.0f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.5f, 0.0f, -0.5f, 0.0f, 0.0f,1.0f, 0.0f, 0.0f, 1.0f, 1.0f
		
	*/
	_Bool hasTexture, hasColor;
	switch(stride){
		case 6: 
			hasTexture = false;
			hasColor = false;
			break;
		case 8: 
			hasTexture = true;
			hasColor = false;
			break;
		case 9: 
			hasTexture = false;
			hasColor = true;
			break;
		case 11:
			hasTexture = true;
			hasColor = true;
			break;
		default:
			std::cout<< "Invalid vertex data given to mesh. Stride given: " << stride << "\nStride must be 6, 8, 9, or 11!" << std::endl;
			exit(1);
	}
	assert(stride >= 6);
  this->vertices = vertices;
  this->verticeCount = verticeCount;
  glGenBuffers(1,  &vbo);
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, stride * verticeCount * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride*sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride*sizeof(float), (void*)(3*sizeof(float)));
  glEnableVertexAttribArray(1);
	/* --- EXAMPLE ---
		std::vector<float> vertices = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,0.5f, 0.5f, 0.5f,  0.0f, 0.0f, //bottom left vertex, normals, UV 0,0
		};
	*/
	int index = 1, offset = 3;
  if(hasTexture){
		index++;
		offset += 3;
    glVertexAttribPointer(index, 2, GL_FLOAT, GL_FALSE, stride, (void*)(offset*sizeof(float)));
    glEnableVertexAttribArray(index);
  }
	if(hasColor){
		index++;
		offset += 
		glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, stride, (void*)(offset*sizeof(float)));
    glEnableVertexAttribArray(index);
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
	shape = GL_TRIANGLES;
  glDrawArrays(shape, 0, verticeCount);
}
