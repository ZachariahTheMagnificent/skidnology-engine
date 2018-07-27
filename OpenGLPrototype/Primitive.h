#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "Vertex.h"
#include <iostream>
enum class ShapeTypes { Plane, Cube, Wedge, CornerWedge, Sphere };

class Primitive{
public:
	static int totalVerticesToRender;
	Vertex* vertices = NULL;
	GLushort* indices = NULL; //indices to vertices array
	unsigned int verticesToStore; //number of vertices to allocate
	unsigned int verticesToRender; //number of vertices to render which make up all the triangles of the shape
	Primitive(ShapeTypes shape) {
		switch (shape) {
		case ShapeTypes::Plane:
			verticesToStore = 4;
			verticesToRender = 6;
			totalVerticesToRender += verticesToRender;
			vertices = new Vertex[verticesToStore];
			vertices[0] = Vertex(glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
			vertices[1] = Vertex(glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
			vertices[2] = Vertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
			vertices[3] = Vertex(glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
			indices = new GLushort[verticesToRender];
			indices[0] = 0;
			indices[1] = 1;
			indices[2] = 2;
			indices[3] = 1;
			indices[4] = 2;
			indices[5] = 3;
			break;
		case ShapeTypes::Cube:
			verticesToStore = 8;
			verticesToRender = 36; //12 triangles * 3 vertices = 36 vertices
			totalVerticesToRender += verticesToRender;
			vertices = new Vertex[verticesToStore];
			vertices[0] = Vertex(glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f));
			vertices[1] = Vertex(glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
			vertices[2] = Vertex(glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			vertices[3] = Vertex(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 0.0f));
			vertices[4] = Vertex(glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			vertices[5] = Vertex(glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
			vertices[6] = Vertex(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 1.0f));
			vertices[7] = Vertex(glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f));
			indices = new GLushort[verticesToRender];
			indices[0] = 0;
			indices[1] = 1;
			indices[2] = 7;
			indices[3] = 1;
			indices[4] = 6;
			indices[5] = 7; //face 1 complete
			indices[6] = 0;
			indices[7] = 3;
			indices[8] = 4;
			indices[9] = 0;
			indices[10] = 7;
			indices[11] = 4; //face 2 complete
			indices[12] = 3;
			indices[13] = 2;
			indices[14] = 5;
			indices[15] = 3;
			indices[16] = 4;
			indices[17] = 5; //face 3 complete
			indices[18] = 2;
			indices[19] = 5;
			indices[20] = 6;
			indices[21] = 6;
			indices[22] = 1;
			indices[23] = 2; //face 4 complete
			indices[24] = 2;
			indices[25] = 3;
			indices[26] = 0;
			indices[27] = 2;
			indices[28] = 1;
			indices[29] = 0; //top face 5 complete
			indices[30] = 4;
			indices[31] = 5;
			indices[32] = 6;
			indices[33] = 6;
			indices[34] = 7;
			indices[35] = 4; //bottom face 6 complete
			break;
		}
	};
	~Primitive() {
		delete[] vertices;
		vertices = NULL;
		delete[] indices;
		indices = NULL;
		totalVerticesToRender -= verticesToRender;
		std::cout << "died" << std::endl;
	};
};
