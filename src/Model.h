#pragma once

#include "BlockTypes.h"
#include <glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include "Mesh.h"
#include "Vertex.h"
#include <string>
#include <list>

class Model
{
private:
	glm::vec3 worldPos;
	bool generated = false;

public:
	Mesh* mesh;
	BlockTypes type;

	glm::vec3 localPos;

	Model(BlockTypes type, glm::vec3 pos);

	void GenerateMesh(vector<bool> size = {true, true, true, true, true, true});

	glm::vec3 GetWorldPos();

	void setGenerated() {
		generated = true;
	}

	void setNotGenerated() {
		generated = false;
	}

	bool getGenerated() {
		return generated;
	}

};

