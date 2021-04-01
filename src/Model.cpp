#include "Model.h"

Model::Model(BlockTypes type, glm::vec3 pos) {
    this->worldPos = pos;
    this->type = type;
    this->setNotGenerated();
}

glm::vec3 Model::GetWorldPos() {
    return this->worldPos;
}

void Model::GenerateMesh(vector<bool> size) {
    this->setGenerated();
    
    int nbVertices = 0;
    int nbIndices = 0;

    for (int i = 0; i < 6; i++) {
        if (size[i]) {
            nbVertices += 4;
            nbIndices += 6;
        }
    }

    Vertex* vertices = new Vertex[nbVertices];

    GLuint* indices = new GLuint[nbIndices];

    int index = 0;
    int indexIndices = 0;
    /*
    vertices[index].position = glm::vec3(-0.5f + worldPos.x, 0.5f + worldPos.y, -0.5f + worldPos.z);
    vertices[index + 1].position = glm::vec3(-0.5f + worldPos.x, -0.5f + worldPos.y, -0.5f + worldPos.z);
    vertices[index + 2].position = glm::vec3(0.5f + worldPos.x, -0.5f + worldPos.y, -0.5f + worldPos.z);
    vertices[index + 3].position = glm::vec3(0.5f + worldPos.x, 0.5f + worldPos.y, -0.5f + worldPos.z);

    vertices[index].color = glm::vec3(1.f, 0.f, 0.f);
    vertices[index + 1].color = glm::vec3(1.f, 0.f, 0.f);
    vertices[index + 2].color = glm::vec3(1.f, 0.f, 0.f);
    vertices[index + 3].color = glm::vec3(1.f, 0.f, 0.f);

    vertices[index].texcoord = glm::vec2(1.f / 16.f * 3.f, 1.f / 16.f * 16.f);
    vertices[index + 1].texcoord = glm::vec2(1.f / 16.f * 3.f, 1.f / 16.f * 15.f);
    vertices[index + 2].texcoord = glm::vec2(1.f / 16.f * 4.f, 1.f / 16.f * 15.f);
    vertices[index + 3].texcoord = glm::vec2(1.f / 16.f * 4.f, 1.f / 16.f * 16.f);

    indices[indexIndices] = 2;
    indices[indexIndices + 1] = 1;
    indices[indexIndices + 2] = 0;
    indices[indexIndices + 3] = 3;
    indices[indexIndices + 4] = 2;
    indices[indexIndices + 5] = 0;

    indexIndices += 6;

    index += 4;

    std::cout << indexIndices;
    std::cout << index;
    */
    
    //Top
    if (size[0]) {
        vertices[index].position = glm::vec3(-0.5f + worldPos.x, 0.5f + worldPos.y, -0.5f + worldPos.z);
        vertices[index + 1].position = glm::vec3(0.5f + worldPos.x, 0.5f + worldPos.y, -0.5f + worldPos.z);
        vertices[index + 2].position = glm::vec3(0.5f + worldPos.x, 0.5f + worldPos.y, 0.5f + worldPos.z);
        vertices[index + 3].position = glm::vec3(-0.5f + worldPos.x, 0.5f + worldPos.y, 0.5f + worldPos.z);

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

    if (size[1]) {
        vertices[index].position = glm::vec3(-0.5f + worldPos.x, -0.5f + worldPos.y, -0.5f + worldPos.z);
        vertices[index + 1].position = glm::vec3(0.5f + worldPos.x, -0.5f + worldPos.y, -0.5f + worldPos.z);
        vertices[index + 2].position = glm::vec3(0.5f + worldPos.x, -0.5f + worldPos.y, 0.5f + worldPos.z);
        vertices[index + 3].position = glm::vec3(-0.5f + worldPos.x, -0.5f + worldPos.y, 0.5f + worldPos.z);

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

    if (size[2]) {
        vertices[index].position = glm::vec3(0.5f + worldPos.x, -0.5f + worldPos.y, -0.5f + worldPos.z);
        vertices[index + 1].position = glm::vec3(0.5f + worldPos.x, 0.5f + worldPos.y, -0.5f + worldPos.z);
        vertices[index + 2].position = glm::vec3(0.5f + worldPos.x, 0.5f + worldPos.y, 0.5f + worldPos.z);
        vertices[index + 3].position = glm::vec3(0.5f + worldPos.x, -0.5f + worldPos.y, 0.5f + worldPos.z);

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

    if (size[3]) {
        vertices[index].position = glm::vec3(-0.5f + worldPos.x, -0.5f + worldPos.y, -0.5f + worldPos.z);
        vertices[index + 1].position = glm::vec3(-0.5f + worldPos.x, 0.5f + worldPos.y, -0.5f + worldPos.z);
        vertices[index + 2].position = glm::vec3(-0.5f + worldPos.x, 0.5f + worldPos.y, 0.5f + worldPos.z);
        vertices[index + 3].position = glm::vec3(-0.5f + worldPos.x, -0.5f + worldPos.y, 0.5f + worldPos.z);

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

    if (size[4]) {
        vertices[index].position = glm::vec3(-0.5f + worldPos.x, -0.5f + worldPos.y, 0.5f + worldPos.z);
        vertices[index + 1].position = glm::vec3(-0.5f + worldPos.x, 0.5f + worldPos.y, 0.5f + worldPos.z);
        vertices[index + 2].position = glm::vec3(0.5f + worldPos.x, 0.5f + worldPos.y, 0.5f + worldPos.z);
        vertices[index + 3].position = glm::vec3(0.5f + worldPos.x, -0.5f + worldPos.y, 0.5f + worldPos.z);

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

    if (size[5]) {
        vertices[index].position = glm::vec3(-0.5f + worldPos.x, -0.5f + worldPos.y, -0.5f + worldPos.z);
        vertices[index + 1].position = glm::vec3(-0.5f + worldPos.x, 0.5f + worldPos.y, -0.5f + worldPos.z);
        vertices[index + 2].position = glm::vec3(0.5f + worldPos.x, 0.5f + worldPos.y, -0.5f + worldPos.z);
        vertices[index + 3].position = glm::vec3(0.5f + worldPos.x, -0.5f + worldPos.y, -0.5f + worldPos.z);

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
    

    /*
    Vertex vertices[] =
    {
        //Front
        glm::vec3(-0.5f + worldPos.x, 0.5f + worldPos.y, -0.5f + worldPos.z),         glm::vec3(1.f, 0.f, 0.f),       glm::vec2(1.f / 16.f * 3.f, 1.f / 16.f * 16.f), //top left
        glm::vec3(-0.5f + worldPos.x, -0.5f + worldPos.y, -0.5f + worldPos.z),       glm::vec3(0.f, 1.f, 0.f),       glm::vec2(1.f / 16.f * 3.f, 1.f / 16.f * 15.f), //bottom left
        glm::vec3(0.5f + worldPos.x, -0.5f + worldPos.y, -0.5f + worldPos.z),        glm::vec3(0.f, 0.f, 1.f),       glm::vec2(1.f / 16.f * 4.f, 1.f / 16.f * 15.f), //bottom right
        glm::vec3(0.5f + worldPos.x, 0.5f + worldPos.y, -0.5f + worldPos.z),        glm::vec3(0.f, 1.f, 1.f),       glm::vec2(1.f / 16.f * 4.f, 1.f / 16.f * 16.f), //top right 

        //Right
        glm::vec3(0.5f + worldPos.x, 0.5f + worldPos.y, 0.5f + worldPos.z),         glm::vec3(1.f, 0.f, 0.f),       glm::vec2(1.f / 16.f * 3.f, 1.f / 16.f * 16.f), //top right
        glm::vec3(0.5f + worldPos.x, -0.5f + worldPos.y, 0.5f + worldPos.z),       glm::vec3(0.f, 1.f, 0.f),       glm::vec2(1.f / 16.f * 3.f, 1.f / 16.f * 15.f), //bottom right

        //Back
        glm::vec3(-0.5f + worldPos.x, 0.5f + worldPos.y, 0.5f + worldPos.z),         glm::vec3(1.f, 0.f, 0.f),       glm::vec2(1.f / 16.f * 4.f, 1.f / 16.f * 16.f), //top left
        glm::vec3(-0.5f + worldPos.x, -0.5f + worldPos.y, 0.5f + worldPos.z),       glm::vec3(0.f, 1.f, 0.f),       glm::vec2(1.f / 16.f * 4.f, 1.f / 16.f * 15.f), //bottom left

        //Bottom
        glm::vec3(-0.5f + worldPos.x, -0.5f + worldPos.y, -0.5f + worldPos.z),         glm::vec3(1.f, 0.f, 0.f),       glm::vec2(1.f / 16.f * 2.f - 0.001f, 1.f / 16.f * 16.f), //top left
        glm::vec3(0.5f + worldPos.x, -0.5f + worldPos.y, -0.5f + worldPos.z),       glm::vec3(0.f, 1.f, 0.f),       glm::vec2(1.f / 16.f * 2.f - 0.001f, 1.f / 16.f * 15.f), //bottom left
        glm::vec3(0.5f + worldPos.x, -0.5f + worldPos.y, 0.5f + worldPos.z),        glm::vec3(0.f, 0.f, 1.f),       glm::vec2(1.f / 16.f * 3.f - 0.001f, 1.f / 16.f * 15.f), //bottom right
        glm::vec3(-0.5f + worldPos.x, -0.5f + worldPos.y, 0.5f + worldPos.z),        glm::vec3(0.f, 1.f, 1.f),       glm::vec2(1.f / 16.f * 3.f - 0.001f, 1.f / 16.f * 16.f), //top right 

        //Top
        glm::vec3(-0.5f + worldPos.x, 0.5f + worldPos.y, -0.5f + worldPos.z),         glm::vec3(1.f, 0.f, 0.f),       glm::vec2(1.f / 16.f * 8.f, 1.f / 16.f * 14.f), //top left
        glm::vec3(0.5f + worldPos.x, 0.5f + worldPos.y, -0.5f + worldPos.z),       glm::vec3(0.f, 1.f, 0.f),       glm::vec2(1.f / 16.f * 8.f, 1.f / 16.f * 13.f), //bottom left
        glm::vec3(0.5f + worldPos.x, 0.5f + worldPos.y, 0.5f + worldPos.z),        glm::vec3(0.f, 0.f, 1.f),       glm::vec2(1.f / 16.f * 9.f, 1.f / 16.f * 13.f), //bottom right
        glm::vec3(-0.5f + worldPos.x, 0.5f + worldPos.y, 0.5f + worldPos.z),        glm::vec3(0.f, 1.f, 1.f),       glm::vec2(1.f / 16.f * 9.f, 1.f / 16.f * 14.f), //top right 
    };
    //unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

    /*
    GLuint indices[] = {
        2, 1, 0,
        3, 2, 0,

        5, 2, 3,
        3, 4, 5,

        7, 5, 4,
        6, 7, 4,

        1, 6, 0,
        1, 7, 6,

        8, 9, 10,
        8, 10, 11,

        14, 13, 12,
        15, 14, 12

    };
    */
    //unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);
    

    /*
    std::list<Vertex> list;

    //if (size[0]) {
        Vertex vert;
        vert.position = glm::vec3(-0.5f + worldPos.x, 0.5f + worldPos.y, -0.5f + worldPos.z);
        vert.color = glm::vec3(1.f, 0.f, 0.f);
        vert.texcoord = glm::vec2(1.f / 16.f * 3.f, 1.f / 16.f * 16.f);

        Vertex vert1;
        vert.position = glm::vec3(-0.5f + worldPos.x, -0.5f + worldPos.y, -0.5f + worldPos.z);
        vert.color = glm::vec3(1.f, 0.f, 0.f);
        vert.texcoord = glm::vec2(1.f / 16.f * 3.f, 1.f / 16.f * 15.f);

        Vertex vert2;
        vert.position = glm::vec3(0.5f + worldPos.x, -0.5f + worldPos.y, -0.5f + worldPos.z);
        vert.color = glm::vec3(1.f, 0.f, 0.f);
        vert.texcoord = glm::vec2(1.f / 16.f * 4.f, 1.f / 16.f * 15.f);

        Vertex vert3;
        vert.position = glm::vec3(0.5f + worldPos.x, 0.5f + worldPos.y, -0.5f + worldPos.z);
        vert.color = glm::vec3(1.f, 0.f, 0.f);
        vert.texcoord = glm::vec2(1.f / 16.f * 4.f, 1.f / 16.f * 16.f);

        list.push_back(vert);
        list.push_back(vert1);
        list.push_back(vert2);
        list.push_back(vert3);
    //}

    Vertex arr[sizeof(list)];
    int k = 0;
    for (Vertex& i : list) {
        arr[k++] = i;
    }
    */

    unsigned nrOfVertices = 4;
    unsigned nrOfIndices = 6;
    

    //mesh = new Mesh(arr, nrOfVertices, indices, nrOfIndices);
    

    mesh = new Mesh(vertices, nbVertices, indices, nbIndices);

    delete[] vertices;
    delete[] indices;
}