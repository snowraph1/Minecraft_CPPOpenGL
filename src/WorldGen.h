#pragma once

#include <glm.hpp>
#include "Chunk.h"
#include "Shader.h"
#include <list>
#include <algorithm>
#include "ThreadPool.h"

class WorldGen
{
private:
	int const CHUNK_X_SIZE = 16;
	int const CHUNK_Y_SIZE = 16;
	int const CHUNK_Z_SIZE = 16;

	int const CHUNK_X = 10;
	int const CHUNK_Z = 10;

	std::vector<glm::vec3> vec =
	{
		glm::vec3(0.f, 1.f, 0.f),
		glm::vec3(0.f, -1.f, 0.f),
		glm::vec3(1.f, 0.f, 0.f),
		glm::vec3(-1.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 1.f),
		glm::vec3(0.f, 0.f, -1.f),
	};

	void GenerateChunkMesh() {

	}

public:
	std::vector<Chunk*> chunks;

	std::vector<Chunk*> GenerateWorld() {

		for (int x = 0; x < CHUNK_X; x++)
		{
			for (int z = 0; z < CHUNK_Z; z++)
			{
				Chunk* chunk = new Chunk(glm::vec3(x * CHUNK_X_SIZE - (CHUNK_X / 2 * CHUNK_X_SIZE), 0, z * CHUNK_Z_SIZE - (CHUNK_Z / 2 * CHUNK_Z_SIZE)));

				chunks.push_back(chunk);
			}
		}

		return chunks;
	}

	void GenerateChunk(glm::vec3 pos) {
		Chunk* chunk = new Chunk(pos);
		chunks.push_back(chunk);

	}

	void RenderChunks(Shader* shader) {
		for (Chunk* i : chunks) {
			if (i->isVaoInit) {
				i->renderChunk(shader);
			}
		}
	}
};

