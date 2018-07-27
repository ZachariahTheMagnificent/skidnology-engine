#pragma once

#include<glm/glm.hpp>

class Vertex{
public:
	glm::vec3 position;
	glm::vec3 color;
	Vertex() {
		position = glm::vec3();
		color = glm::vec3();
	};
	Vertex(glm::vec3 pos, glm::vec3 col) {
		position = pos;
		color = col;
	};
	~Vertex() {

	};
};

