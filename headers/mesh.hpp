#pragma once
#include <GL/glew.h>
#include <GL/gl.h>
#include<vector>
class Mesh{
	public:
		Mesh(std::vector<float> vertices,std::vector<unsigned int> indices, int verticeCount);
		~Mesh();
		void Draw();	
		GLuint vbo, vao,ebo;
		int verticeCount, indicesSize;

};
