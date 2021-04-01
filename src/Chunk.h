#pragma once

#include <glm.hpp>
#include "Model.h"
#include <list>
#include <stdlib.h>
#include <gtc/noise.hpp>
#include "Mesh.h"
#include <gtc/noise.hpp>
#include <ctime>

class Chunk
{
private:
	const int SIZE_Y = 60;
	const int SIZE_X = 16;
	const int SIZE_Z = 16;

	Model* blocks[16][60][16];

	std::vector<glm::vec3> vec = 
	{	
		glm::vec3(0.f, 1.f, 0.f),
		glm::vec3(0.f, -1.f, 0.f),
		glm::vec3(1.f, 0.f, 0.f),
		glm::vec3(-1.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 1.f),
		glm::vec3(0.f, 0.f, -1.f),
	};

	bool TestBlock(glm::vec3 pos);

public:
	clock_t updateTime;

	Mesh* mesh;

	bool isGenerated = false;

	bool isVaoInit = false;

	glm::vec3 worldPos;

	Chunk* borderChunks[4];

	Chunk(glm::vec3 pos);

	int nbVertices;
	int nbIndices;
	Vertex* vertices;
	GLuint* indices;

	void SetBorderChunk(int index, Chunk* chunk);

	void renderChunk(Shader* shader);

	void GenerateChunkMesh();

	void UpdateNeighboor();

	void GenerateChunk() {
		for (int x = 0; x < this->SIZE_X; x++) {
			for (int z = 0; z < this->SIZE_Z; z++) {

				glm::vec3 testPos(x - SIZE_X / 2 + worldPos.x, worldPos.y, z - SIZE_Z / 2 + worldPos.z);

				float height = 3 * glm::simplex(glm::vec2(testPos.x / 90, testPos.z / 90)) + 0.5f * glm::simplex(glm::vec2(3 * (testPos.x / 40), 2 * (testPos.z / 40)));

				height += 1;
				height = height / 2;

				height = height * 13 + 20;

				height = glm::floor(height);


				for (int y = 0; y < SIZE_Y; y++) {
					if (y < height) {
						glm::vec3 chunkPos(x - SIZE_X / 2 + worldPos.x, y + worldPos.y, z - SIZE_Z / 2 + worldPos.z);

						Model* block = new Model(Grass, chunkPos);

						block->localPos = glm::vec3(x, y, z);

						blocks[x][y][z] = block;
					}
					else {
						glm::vec3 chunkPos(x - SIZE_X / 2 + worldPos.x, y + worldPos.y, z - SIZE_Z / 2 + worldPos.z);

						Model* block = new Model(Air, chunkPos);

						block->localPos = glm::vec3(x, y, z);

						blocks[x][y][z] = block;
					}
				}
			}
		}
	}
};

