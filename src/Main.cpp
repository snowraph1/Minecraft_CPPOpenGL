#include"lib.h"

using namespace std;

float speed = 10;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

glm::vec3 camDirection;
glm::vec3 worldUp(0.f, 1.f, 0.f);

float dt = 0.f;
float curTime = 0.f;
float lastTime = 0.f;

void UpdateInput(GLFWwindow* window, Camera& camera)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    glm::vec3 camDirNormalized = glm::normalize(camDirection);
    glm::vec3 camCross = glm::normalize(glm::cross(camDirNormalized, worldUp));

    if (camCross == glm::vec3(0.f)) {
        camCross = glm::vec3(1.f, 0.f, 0.f);
    }

    float newSpeed = speed * dt;

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.move(worldUp * newSpeed);

    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        camera.move(worldUp * -newSpeed);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) 
    {
        camera.move(glm::normalize(glm::vec3(camDirNormalized.x, 0.f, camDirNormalized.z)) * newSpeed);
    }
   
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera.move(glm::normalize(glm::vec3(camDirNormalized.x, 0.f, camDirNormalized.z)) * -newSpeed);
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera.move(camCross * -newSpeed);
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera.move(camCross * newSpeed);
    }
}

double lastX = 0.0;
double lastY = 0.0;
double mouseX = 0.0;
double mouseY = 0.0;
double mouseOffsetX = 0.0;
double mouseOPffsetY = 0.0;
bool firstMouse = true;

float yaw = 0.f;
float pitch = 0.f;

void mouse_callback(GLFWwindow* window, double xpos, double ypos) 
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    camDirection = direction;
}

void UpdateDt() {
    curTime = static_cast<float>(glfwGetTime());
    dt = curTime - lastTime;
    lastTime = curTime;
}

vector<Chunk*> chunks;

void CheckChunkBorder() {
    for (Chunk* i : chunks)
    {
        for (Chunk* t : chunks)
        {
            if (t->worldPos == (i->worldPos + glm::vec3(16.f, 0.f, 0.f))) {
                i->borderChunks[0] = t;
            }

            if (t->worldPos == (i->worldPos + glm::vec3(-16.f, 0.f, 0.f))) {
                i->borderChunks[1] = t;
            }

            if (t->worldPos == (i->worldPos + glm::vec3(0.f, 0.f, 16.f))) {
                i->borderChunks[2] = t;
            }

            if (t->worldPos == (i->worldPos + glm::vec3(0.f, 0.f, -16.f))) {
                i->borderChunks[3] = t;
            }
        }
    }
}

Chunk* tempChunk;

void GenerateChunk() {

    tempChunk->GenerateChunk();
}

Chunk* tempMesh;

void test(Chunk* alo) {
    alo->GenerateChunkMesh();
    alo->isGenerated = true;
}

bool findChunk(glm::vec3 pos, clock_t time) {
    for (Chunk* i : chunks) {
        if (i->worldPos == pos) {
            i->updateTime = time;
            return true;
        }
    }

    return false;
}

Chunk* findReturnChunk(glm::vec3 pos) {
    for (Chunk* i : chunks) {
        if (i->worldPos == pos) {
            return i;
        }
    }

    return NULL;
}

WorldGen worldGen = WorldGen();

void GenerateSingleChunk(glm::vec3 pos, clock_t time) {
    Chunk* chunk = new Chunk(pos);
    chunk->GenerateChunk();
    chunk->isGenerated = true;
    chunk->updateTime = time;

    Chunk* chk = findReturnChunk(glm::vec3(16.f + pos.x, 0.f, 0.f + pos.z));
    if (chk != NULL) {
        chunk->borderChunks[0] = chk;
        chk->borderChunks[1] = chunk;
    }

    chk = findReturnChunk(glm::vec3(-16.f + pos.x, 0.f, 0.f + pos.z));
    if (chk != NULL) {
        chunk->borderChunks[1] = chk;
        chk->borderChunks[0] = chunk;
    }

    chk = findReturnChunk(glm::vec3(0.f + pos.x, 0.f, 16.f + pos.z));
    if (chk != NULL) {
        chunk->borderChunks[2] = chk;
        chk->borderChunks[3] = chunk;
    }

    chk = findReturnChunk(glm::vec3(0.f + pos.x, 0.f, -16.f + pos.z));
    if (chk != NULL) {
        chunk->borderChunks[3] = chk;
        chk->borderChunks[2] = chunk;
    }

    chunk->UpdateNeighboor();

    chunk->GenerateChunkMesh();

    chunks.push_back(chunk);
}

glm::vec3 oldPos;

ThreadPool* pool = new ThreadPool(4);

void petitTest(Camera camera) {
    glm::vec3 playerChunkPos;
    playerChunkPos.x = glm::round(camera.getCameraWorldPosition().x / 16) * 16;
    playerChunkPos.z = glm::round(camera.getCameraWorldPosition().z / 16) * 16;

    if (playerChunkPos != oldPos) {

        clock_t time = clock();

        for (int x = playerChunkPos.x - (3 * 16); x < playerChunkPos.x + (3 * 16); x += 16) {
            for (int z = playerChunkPos.z - (3 * 16); z < playerChunkPos.z + (3 * 16); z += 16) {
                if (!findChunk(glm::vec3(x, 0, z), time)) {
                    //pool->enqueue(GenerateSingleChunk, glm::vec3(x, 0, playerChunkPos.z + (4 * 16)));
                    GenerateSingleChunk(glm::vec3(x, 0, z), time);
                    //pool->enqueue(GenerateSingleChunk, glm::vec3(x, 0, z), time);
                }
            }
        }

        for (Chunk* i : chunks) {
            if (i->updateTime != time) {
                remove(chunks.begin(), chunks.end(), i);
            }
        }

        /*
            if (playerChunkPos.z > oldPos.z) {
                for (int x = playerChunkPos.x - (3 * 16); x < playerChunkPos.x + (3 * 16); x += 16) {
                    if (!findChunk(glm::vec3(x, 0, playerChunkPos.z + (4 * 16)))) {
                        //pool->enqueue(GenerateSingleChunk, glm::vec3(x, 0, playerChunkPos.z + (4 * 16)));
                        GenerateSingleChunk(glm::vec3(x, 0, playerChunkPos.z + (4 * 16)));
                    }

                    findChunk(glm::vec3(x, 0, playerChunkPos.z - (5 * 16)), true);
                }
            }
            else {
                for (int x = playerChunkPos.x - (3 * 16); x < playerChunkPos.x + (3 * 16); x += 16) {
                    if (!findChunk(glm::vec3(x, 0, playerChunkPos.z - (4 * 16)))) {
                        //pool->enqueue(GenerateSingleChunk, glm::vec3(x, 0, playerChunkPos.z + (4 * 16)));
                        GenerateSingleChunk(glm::vec3(x, 0, playerChunkPos.z - (4 * 16)));
                    }

                    findChunk(glm::vec3(x, 0, playerChunkPos.z + (5 * 16)), true);
                }
            }

            if (playerChunkPos.x > oldPos.x) {
                for (int z = playerChunkPos.z - (3 * 16); z < playerChunkPos.z + (3 * 16); z += 16) {
                    if (!findChunk(glm::vec3(playerChunkPos.x + (4 * 16), 0, z))) {
                        //pool->enqueue(GenerateSingleChunk, glm::vec3(x, 0, playerChunkPos.z + (4 * 16)));
                        GenerateSingleChunk(glm::vec3(playerChunkPos.x + (4 * 16), 0, z));
                    }

                    findChunk(glm::vec3(playerChunkPos.x - (5 * 16), 0, z), true);
                }
            }
            else {
                for (int z = playerChunkPos.z - (3 * 16); z < playerChunkPos.z + (3 * 16); z += 16) {
                    if (!findChunk(glm::vec3(playerChunkPos.x - (4 * 16), 0, z))) {
                        //pool->enqueue(GenerateSingleChunk, glm::vec3(x, 0, playerChunkPos.z + (4 * 16)));
                        GenerateSingleChunk(glm::vec3(playerChunkPos.x - (4 * 16), 0, z));
                    }

                    findChunk(glm::vec3(playerChunkPos.x + (5 * 16), 0, z), true);
                }
            }
            */

        oldPos = playerChunkPos;
    }
}

int const CHUNK_X_SIZE = 16;
int const CHUNK_Y_SIZE = 16;
int const CHUNK_Z_SIZE = 16;

int const CHUNK_X = 6;
int const CHUNK_Z = 6;

void GenerateWorld() {

    int x, z;
    int length = 3;
    float angle = 0.0f;
    float interval = 0.1f;

    for (int x = 0; x < CHUNK_X; x++)
    {
        for (int z = 0; z < CHUNK_Z; z++)
        {
            Chunk* chunk = new Chunk(glm::vec3(x * CHUNK_X_SIZE - (CHUNK_X / 2 * CHUNK_X_SIZE), 0, z * CHUNK_Z_SIZE - (CHUNK_Z / 2 * CHUNK_Z_SIZE)));

            chunks.push_back(chunk);
        }
    }
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    int frameBufferWidth = 0;
    int frameBufferheight = 0;

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1600, 900, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /*make sur the window is the right size*/
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferheight);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    
    if (glewInit() != GLEW_OK) {
        cout << "Glew pas ok \n";
        glfwTerminate();
    }

    //OPENGL OPTIONS
    //glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glDepthMask(GL_TRUE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS); // Or GL_LEQUAL

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    //Shaders
    Shader core_program("vertex_core.glsl", "fragment_core.glsl");

    //TEXTURE
    int image_width = 0;
    int image_height = 0;
    unsigned char* image = SOIL_load_image("atlas.png", &image_width, &image_height, NULL, SOIL_LOAD_RGBA);

    GLuint texture0;
    glGenTextures(1, &texture0);
    glBindTexture(GL_TEXTURE_2D, texture0);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    if (image) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        cout << "texture pas load \n";
    }

    glActiveTexture(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    SOIL_free_image_data(image);

    glm::vec3 camPosition(0.f, 30.f, 2.f);
    glm::vec3 camFront = glm::vec3(0.f, 0.f, -1.f);
    Camera camera = Camera(90, 0.1f, 1000.f, frameBufferWidth, frameBufferheight, glm::vec3 (0.f, 30.f, 2.f), glm::vec3(0.f, 0.f, -1.f));
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);

    core_program.use();

    GenerateWorld();

    for (Chunk* i : chunks) {
        tempChunk = i;
        tempChunk->GenerateChunk();
        //pool->enqueue(GenerateChunk);
    }

    //pool->bonjour();

    CheckChunkBorder();

    for (Chunk* i : chunks) {
        tempMesh = i;
        pool->enqueue(test, i);
    }

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        //UPDATE INPUT ---
        glfwPollEvents();

        //UPDATE ---
        UpdateDt();
        UpdateInput(window, camera);
        camera.changeDirection(camDirection);
        //pool->enqueue(petitTest, camera);
        petitTest(camera);

        //cout << playerChunkPos.x << ", " << playerChunkPos.z << "\n";
        if (chunks.size() > 0) {
            for (Chunk* i : chunks)
            {
                if (i != NULL)
                    if (i->isGenerated && !i->isVaoInit) {
                        i->mesh = new Mesh(i->vertices, i->nbVertices, i->indices, i->nbIndices);
                        i->isVaoInit = true;
                    }
            }
        }

        //DRAW ---      
        //clear
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);

        //UpdateCamera
        glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferheight);
        core_program.setMat4fv(camera.getWorldToViewMatrix(), "ViewMatrix");
        core_program.setMat4fv(camera.getProjectionMatrix(), "ProjectionMatrix");

        //use a program
        core_program.use();

        //activate texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture0);

        //bind vertex array object
        //glBindVertexArray(VAO);

        //draw
        //glDrawElements(GL_TRIANGLES, nrOfIndices, GL_UNSIGNED_INT, 0);
        //chunk.renderChunk(&core_program);
        //chunk1.renderChunk(&core_program);

        if (chunks.size() > 0) {
            for (Chunk* i : chunks) {
                if (i->isGenerated)
                if (i->isVaoInit) {
                    i->renderChunk(&core_program);
                }
            }

            //worldGen.RenderChunks(&core_program);
        }

        //end draw
        glfwSwapBuffers(window);
        glFlush();

        glBindVertexArray(0);
        glUseProgram(0);
        glActiveTexture(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    //END OF PROGRAM
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}