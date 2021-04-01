#include "Chunk.h"

Chunk::Chunk(glm::vec3 pos) {
    worldPos = pos;
}

void Chunk::UpdateNeighboor () {
    for (int i = 0; i < 4; i++) {
        if (borderChunks[i] != NULL) {
            borderChunks[i]->GenerateChunkMesh();
        }
    }
}

void Chunk::GenerateChunkMesh() {

    int nbVertices = 0;
    int nbIndices = 0;

    for (int x = 0; x < this->SIZE_X; x++) {
        for (int z = 0; z < this->SIZE_Z; z++) {
            for (int y = 0; y < SIZE_Y; y++) {
                if (blocks[x][y][z]->type != Air) {
                    if (TestBlock(blocks[x][y][z]->localPos + glm::vec3(0.f, 1.f, 0.f))) {
                        nbVertices += 4;
                        nbIndices += 6;
                    }

                    if (TestBlock(blocks[x][y][z]->localPos + glm::vec3(0.f, -1.f, 0.f))) {
                        nbVertices += 4;
                        nbIndices += 6;
                    }

                    if (TestBlock(blocks[x][y][z]->localPos + glm::vec3(1.f, 0.f, 0.f))) {
                        nbVertices += 4;
                        nbIndices += 6;
                    }

                    if (TestBlock(blocks[x][y][z]->localPos + glm::vec3(-1.f, 0.f, 0.f))) {
                        nbVertices += 4;
                        nbIndices += 6;
                    }

                    if (TestBlock(blocks[x][y][z]->localPos + glm::vec3(0.f, 0.f, 1.f))) {
                        nbVertices += 4;
                        nbIndices += 6;
                    }

                    if (TestBlock(blocks[x][y][z]->localPos + glm::vec3(0.f, 0.f, -1.f))) {
                        nbVertices += 4;
                        nbIndices += 6;
                    }
                }
            }
        }
    }

    Vertex* vertices = new Vertex[nbVertices];

    GLuint* indices = new GLuint[nbIndices];

    int index = 0;
    int indexIndices = 0;

    for (int x = 0; x < this->SIZE_X; x++) {
        for (int z = 0; z < this->SIZE_Z; z++) {
            for (int y = 0; y < SIZE_Y; y++) {
                if (blocks[x][y][z]->type != Air) {
                    if (TestBlock(blocks[x][y][z]->localPos + glm::vec3(0.f, 1.f, 0.f))) {
                        vertices[index].position = glm::vec3(-0.5f + blocks[x][y][z]->GetWorldPos().x, 0.5f + blocks[x][y][z]->GetWorldPos().y, -0.5f + blocks[x][y][z]->GetWorldPos().z);
                        vertices[index + 1].position = glm::vec3(0.5f + blocks[x][y][z]->GetWorldPos().x, 0.5f + blocks[x][y][z]->GetWorldPos().y, -0.5f + blocks[x][y][z]->GetWorldPos().z);
                        vertices[index + 2].position = glm::vec3(0.5f + blocks[x][y][z]->GetWorldPos().x, 0.5f + blocks[x][y][z]->GetWorldPos().y, 0.5f + blocks[x][y][z]->GetWorldPos().z);
                        vertices[index + 3].position = glm::vec3(-0.5f + blocks[x][y][z]->GetWorldPos().x, 0.5f + blocks[x][y][z]->GetWorldPos().y, 0.5f + blocks[x][y][z]->GetWorldPos().z);

                        vertices[index].color = glm::vec3(1.f, 0.f, 0.f);
                        vertices[index + 1].color = glm::vec3(1.f, 0.f, 0.f);
                        vertices[index + 2].color = glm::vec3(1.f, 0.f, 0.f);
                        vertices[index + 3].color = glm::vec3(1.f, 0.f, 0.f);

                        vertices[index].texcoord = glm::vec2(1.f / 16.f * 8.f, 1.f / 16.f * 14.f);
                        vertices[index + 1].texcoord = glm::vec2(1.f / 16.f * 8.f, 1.f / 16.f * 13.f);
                        vertices[index + 2].texcoord = glm::vec2(1.f / 16.f * 9.f, 1.f / 16.f * 13.f);
                        vertices[index + 3].texcoord = glm::vec2(1.f / 16.f * 9.f, 1.f / 16.f * 14.f);

                        indices[indexIndices] = index + 2;
                        indices[indexIndices + 1] = index + 1;
                        indices[indexIndices + 2] = index;
                        indices[indexIndices + 3] = index + 3;
                        indices[indexIndices + 4] = index + 2;
                        indices[indexIndices + 5] = index;

                        indexIndices += 6;

                        index += 4;
                    }

                    if (TestBlock(blocks[x][y][z]->localPos + glm::vec3(0.f, -1.f, 0.f))) {
                        vertices[index].position = glm::vec3(-0.5f + blocks[x][y][z]->GetWorldPos().x, -0.5f + blocks[x][y][z]->GetWorldPos().y, -0.5f + blocks[x][y][z]->GetWorldPos().z);
                        vertices[index + 1].position = glm::vec3(0.5f + blocks[x][y][z]->GetWorldPos().x, -0.5f + blocks[x][y][z]->GetWorldPos().y, -0.5f + blocks[x][y][z]->GetWorldPos().z);
                        vertices[index + 2].position = glm::vec3(0.5f + blocks[x][y][z]->GetWorldPos().x, -0.5f + blocks[x][y][z]->GetWorldPos().y, 0.5f + blocks[x][y][z]->GetWorldPos().z);
                        vertices[index + 3].position = glm::vec3(-0.5f + blocks[x][y][z]->GetWorldPos().x, -0.5f + blocks[x][y][z]->GetWorldPos().y, 0.5f + blocks[x][y][z]->GetWorldPos().z);

                        vertices[index].color = glm::vec3(1.f, 0.f, 0.f);
                        vertices[index + 1].color = glm::vec3(1.f, 0.f, 0.f);
                        vertices[index + 2].color = glm::vec3(1.f, 0.f, 0.f);
                        vertices[index + 3].color = glm::vec3(1.f, 0.f, 0.f);

                        vertices[index].texcoord = glm::vec2(1.f / 16.f * 2.f - 0.001f, 1.f / 16.f * 16.f);
                        vertices[index + 1].texcoord = glm::vec2(1.f / 16.f * 2.f - 0.001f, 1.f / 16.f * 15.f);
                        vertices[index + 2].texcoord = glm::vec2(1.f / 16.f * 3.f - 0.001f, 1.f / 16.f * 15.f);
                        vertices[index + 3].texcoord = glm::vec2(1.f / 16.f * 3.f - 0.001f, 1.f / 16.f * 16.f);

                        indices[indexIndices] = index;
                        indices[indexIndices + 1] = index + 1;
                        indices[indexIndices + 2] = index + 2;
                        indices[indexIndices + 3] = index;
                        indices[indexIndices + 4] = index + 2;
                        indices[indexIndices + 5] = index + 3;

                        indexIndices += 6;

                        index += 4;
                    }

                    if (TestBlock(blocks[x][y][z]->localPos + glm::vec3(1.f, 0.f, 0.f))) {
                        vertices[index].position = glm::vec3(0.5f + blocks[x][y][z]->GetWorldPos().x, -0.5f + blocks[x][y][z]->GetWorldPos().y, -0.5f + blocks[x][y][z]->GetWorldPos().z);
                        vertices[index + 1].position = glm::vec3(0.5f + blocks[x][y][z]->GetWorldPos().x, 0.5f + blocks[x][y][z]->GetWorldPos().y, -0.5f + blocks[x][y][z]->GetWorldPos().z);
                        vertices[index + 2].position = glm::vec3(0.5f + blocks[x][y][z]->GetWorldPos().x, 0.5f + blocks[x][y][z]->GetWorldPos().y, 0.5f + blocks[x][y][z]->GetWorldPos().z);
                        vertices[index + 3].position = glm::vec3(0.5f + blocks[x][y][z]->GetWorldPos().x, -0.5f + blocks[x][y][z]->GetWorldPos().y, 0.5f + blocks[x][y][z]->GetWorldPos().z);

                        vertices[index].color = glm::vec3(1.f, 0.f, 0.f);
                        vertices[index + 1].color = glm::vec3(1.f, 0.f, 0.f);
                        vertices[index + 2].color = glm::vec3(1.f, 0.f, 0.f);
                        vertices[index + 3].color = glm::vec3(1.f, 0.f, 0.f);

                        vertices[index].texcoord = glm::vec2(1.f / 16.f * 3.f, 1.f / 16.f * 15.f);
                        vertices[index + 1].texcoord = glm::vec2(1.f / 16.f * 3.f, 1.f / 16.f * 16.f);
                        vertices[index + 2].texcoord = glm::vec2(1.f / 16.f * 4.f, 1.f / 16.f * 16.f);
                        vertices[index + 3].texcoord = glm::vec2(1.f / 16.f * 4.f, 1.f / 16.f * 15.f);

                        indices[indexIndices] = index;
                        indices[indexIndices + 1] = index + 1;
                        indices[indexIndices + 2] = index + 2;
                        indices[indexIndices + 3] = index;
                        indices[indexIndices + 4] = index + 2;
                        indices[indexIndices + 5] = index + 3;

                        indexIndices += 6;

                        index += 4;
                    }

                    if (TestBlock(blocks[x][y][z]->localPos + glm::vec3(-1.f, 0.f, 0.f))) {
                        vertices[index].position = glm::vec3(-0.5f + blocks[x][y][z]->GetWorldPos().x, -0.5f + blocks[x][y][z]->GetWorldPos().y, -0.5f + blocks[x][y][z]->GetWorldPos().z);
                        vertices[index + 1].position = glm::vec3(-0.5f + blocks[x][y][z]->GetWorldPos().x, 0.5f + blocks[x][y][z]->GetWorldPos().y, -0.5f + blocks[x][y][z]->GetWorldPos().z);
                        vertices[index + 2].position = glm::vec3(-0.5f + blocks[x][y][z]->GetWorldPos().x, 0.5f + blocks[x][y][z]->GetWorldPos().y, 0.5f + blocks[x][y][z]->GetWorldPos().z);
                        vertices[index + 3].position = glm::vec3(-0.5f + blocks[x][y][z]->GetWorldPos().x, -0.5f + blocks[x][y][z]->GetWorldPos().y, 0.5f + blocks[x][y][z]->GetWorldPos().z);

                        vertices[index].color = glm::vec3(1.f, 0.f, 0.f);
                        vertices[index + 1].color = glm::vec3(1.f, 0.f, 0.f);
                        vertices[index + 2].color = glm::vec3(1.f, 0.f, 0.f);
                        vertices[index + 3].color = glm::vec3(1.f, 0.f, 0.f);

                        vertices[index].texcoord = glm::vec2(1.f / 16.f * 3.f, 1.f / 16.f * 15.f);
                        vertices[index + 1].texcoord = glm::vec2(1.f / 16.f * 3.f, 1.f / 16.f * 16.f);
                        vertices[index + 2].texcoord = glm::vec2(1.f / 16.f * 4.f, 1.f / 16.f * 16.f);
                        vertices[index + 3].texcoord = glm::vec2(1.f / 16.f * 4.f, 1.f / 16.f * 15.f);

                        indices[indexIndices] = index + 2;
                        indices[indexIndices + 1] = index + 1;
                        indices[indexIndices + 2] = index;
                        indices[indexIndices + 3] = index + 3;
                        indices[indexIndices + 4] = index + 2;
                        indices[indexIndices + 5] = index;

                        indexIndices += 6;

                        index += 4;
                    }

                    if (TestBlock(blocks[x][y][z]->localPos + glm::vec3(0.f, 0.f, 1.f))) {
                        vertices[index].position = glm::vec3(-0.5f + blocks[x][y][z]->GetWorldPos().x, -0.5f + blocks[x][y][z]->GetWorldPos().y, 0.5f + blocks[x][y][z]->GetWorldPos().z);
                        vertices[index + 1].position = glm::vec3(-0.5f + blocks[x][y][z]->GetWorldPos().x, 0.5f + blocks[x][y][z]->GetWorldPos().y, 0.5f + blocks[x][y][z]->GetWorldPos().z);
                        vertices[index + 2].position = glm::vec3(0.5f + blocks[x][y][z]->GetWorldPos().x, 0.5f + blocks[x][y][z]->GetWorldPos().y, 0.5f + blocks[x][y][z]->GetWorldPos().z);
                        vertices[index + 3].position = glm::vec3(0.5f + blocks[x][y][z]->GetWorldPos().x, -0.5f + blocks[x][y][z]->GetWorldPos().y, 0.5f + blocks[x][y][z]->GetWorldPos().z);

                        vertices[index].color = glm::vec3(1.f, 0.f, 0.f);
                        vertices[index + 1].color = glm::vec3(1.f, 0.f, 0.f);
                        vertices[index + 2].color = glm::vec3(1.f, 0.f, 0.f);
                        vertices[index + 3].color = glm::vec3(1.f, 0.f, 0.f);

                        vertices[index].texcoord = glm::vec2(1.f / 16.f * 3.f, 1.f / 16.f * 15.f);
                        vertices[index + 1].texcoord = glm::vec2(1.f / 16.f * 3.f, 1.f / 16.f * 16.f);
                        vertices[index + 2].texcoord = glm::vec2(1.f / 16.f * 4.f, 1.f / 16.f * 16.f);
                        vertices[index + 3].texcoord = glm::vec2(1.f / 16.f * 4.f, 1.f / 16.f * 15.f);

                        indices[indexIndices] = index + 2;
                        indices[indexIndices + 1] = index + 1;
                        indices[indexIndices + 2] = index;
                        indices[indexIndices + 3] = index + 3;
                        indices[indexIndices + 4] = index + 2;
                        indices[indexIndices + 5] = index;

                        indexIndices += 6;

                        index += 4;
                    }

                    if (TestBlock(blocks[x][y][z]->localPos + glm::vec3(0.f, 0.f, -1.f))) {
                        vertices[index].position = glm::vec3(-0.5f + blocks[x][y][z]->GetWorldPos().x, -0.5f + blocks[x][y][z]->GetWorldPos().y, -0.5f + blocks[x][y][z]->GetWorldPos().z);
                        vertices[index + 1].position = glm::vec3(-0.5f + blocks[x][y][z]->GetWorldPos().x, 0.5f + blocks[x][y][z]->GetWorldPos().y, -0.5f + blocks[x][y][z]->GetWorldPos().z);
                        vertices[index + 2].position = glm::vec3(0.5f + blocks[x][y][z]->GetWorldPos().x, 0.5f + blocks[x][y][z]->GetWorldPos().y, -0.5f + blocks[x][y][z]->GetWorldPos().z);
                        vertices[index + 3].position = glm::vec3(0.5f + blocks[x][y][z]->GetWorldPos().x, -0.5f + blocks[x][y][z]->GetWorldPos().y, -0.5f + blocks[x][y][z]->GetWorldPos().z);

                        vertices[index].color = glm::vec3(1.f, 0.f, 0.f);
                        vertices[index + 1].color = glm::vec3(1.f, 0.f, 0.f);
                        vertices[index + 2].color = glm::vec3(1.f, 0.f, 0.f);
                        vertices[index + 3].color = glm::vec3(1.f, 0.f, 0.f);

                        vertices[index].texcoord = glm::vec2(1.f / 16.f * 3.f, 1.f / 16.f * 15.f);
                        vertices[index + 1].texcoord = glm::vec2(1.f / 16.f * 3.f, 1.f / 16.f * 16.f);
                        vertices[index + 2].texcoord = glm::vec2(1.f / 16.f * 4.f, 1.f / 16.f * 16.f);
                        vertices[index + 3].texcoord = glm::vec2(1.f / 16.f * 4.f, 1.f / 16.f * 15.f);

                        indices[indexIndices] = index;
                        indices[indexIndices + 1] = index + 1;
                        indices[indexIndices + 2] = index + 2;
                        indices[indexIndices + 3] = index;
                        indices[indexIndices + 4] = index + 2;
                        indices[indexIndices + 5] = index + 3;

                        indexIndices += 6;

                        index += 4;
                    }
                }
            }
        }
    }

    //this->mesh = new Mesh(vertices, nbVertices, indices, nbIndices);
    this->nbVertices = nbVertices;
    this->nbIndices = nbIndices;
    this->vertices = vertices;
    this->indices = indices;
}

bool Chunk::TestBlock(glm::vec3 pos) {
    if (pos.x == SIZE_X && borderChunks[0] != NULL) {
        if (borderChunks[0]->blocks[0][(int)pos.y][(int)pos.z]->type == 0) {
            return false;
        }
    }

    if (pos.x < 0 && borderChunks[1] != NULL) {
        if (borderChunks[1]->blocks[15][(int)pos.y][(int)pos.z]->type == 0) {
            return false;
        }
    }

    if (pos.z == SIZE_Z && borderChunks[2] != NULL) {
        cout << "test";
        if (borderChunks[2]->blocks[(int)pos.x][(int)pos.y][0]->type == 0) {
            return false;
        }
    }

    if (pos.z < 0 && borderChunks[3] != NULL) {
        if (borderChunks[3]->blocks[(int)pos.x][(int)pos.y][15]->type == 0) {
            return false;
        }
    }

    if (pos.x == SIZE_X || pos.z == SIZE_Z || pos.y == SIZE_Y || pos.x < 0 || pos.y < 0 || pos.z < 0) {
        return true;
    }

    if (blocks[(int)pos.x][(int)pos.y][(int)pos.z]->type == 2)
    {
        return true;
    }

    return false;
}

void Chunk::renderChunk(Shader* shader) {
    if (isGenerated) {
        mesh->Render(shader);
    }
}
/// <summary>
/// Set border chunk
/// </summary>
/// <param name="index">0 = top, 1 = right, 2 = bottom, 3 = left</param>
void Chunk::SetBorderChunk(int index, Chunk* chunk) {
	borderChunks[index] = chunk;
}

