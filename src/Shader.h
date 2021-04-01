#pragma once

#include <glew.h>
#include <GLFW/glfw3.h>
#include<string>
#include <iostream>
#include <fstream>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>

using namespace std;

class Shader
{
private:
	GLuint id;

	std::string loadShaderSource(string fileName) {
        string temp = "";
        string src = "";
        ifstream in_file;

        //vertex
        in_file.open(fileName);

        if (in_file.is_open()) {
            while (getline(in_file, temp))
            {
                src += temp + "\n";
            }
        }
        else {
            cout << "SHADER ERROR : FILE NOT OPEN. FILE :" << fileName << "\n";
        }

        in_file.close();

        return src;
	}

	GLuint loadShader(GLenum type, string fileName) {
        char infoLog[512];
        GLint success;

        GLuint shader = glCreateShader(type);
        std::string str_src = loadShaderSource(fileName);
        const GLchar* src = str_src.c_str();
        glShaderSource(shader, 1, &src, NULL);
        glCompileShader(shader);

        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            cout << "SHADER ERROR : " << type << " SHADER NOT LOADED" << "\n";
        }

        return shader;
	}

	void linkProgram(GLint vertexShader, GLuint geometryShader, GLuint fragmentShader) {
        char infoLog[512];
        GLint success;

        this->id = glCreateProgram();

        glAttachShader(this->id, vertexShader);

        if (geometryShader) {
            glAttachShader(this->id, geometryShader);
        }

        glAttachShader(this->id, fragmentShader);

        glLinkProgram(this->id);

        glGetProgramiv(this->id, GL_LINK_STATUS, &success);
        if (!success) {
            cout << "SHADER ERROR : LINKING FAILED \n";
        }

        glUseProgram(0);
	}

public:

	Shader(string vertexFile, string fragmentFile, string geometryFile = "") {
        GLuint vertexShader = 0;
        GLuint geometryShader = 0;
        GLuint fragmentShader = 0;

        vertexShader = loadShader(GL_VERTEX_SHADER, vertexFile);

        if (geometryFile != "") {
            geometryShader = loadShader(GL_GEOMETRY_SHADER, geometryFile);
        }

        fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentFile);

        this->linkProgram(vertexShader, geometryShader, fragmentShader);

        glDeleteShader(vertexShader);
        glDeleteShader(geometryShader);
        glDeleteShader(fragmentShader);

        cout << "Tout est good";
	}

    ~Shader() {

    }

    void use() {
        glUseProgram(this->id);
    }

    void unuse() {
        glUseProgram(0);
    }

    void set1i(GLint value, const GLchar* name) {
        this->use();

        glUniform1i(glGetUniformLocation(this->id, name), value);

        this->unuse();
    }

    void set1f(GLfloat value, const GLchar* name) {
        this->use();

        glUniform1f(glGetUniformLocation(this->id, name), value);

        this->unuse();
    }

    void setVec2f(glm::fvec2 value, const GLchar* name) {
        this->use();

        glUniform2fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));

        this->unuse();
    }

    void setVec3f(glm::fvec3 value, const GLchar* name) {
        this->use();

        glUniform3fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));

        this->unuse();
    }

    void setVec4f(glm::fvec4 value, const GLchar* name) {
        this->use();

        glUniform4fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));

        this->unuse();
    }

    void setMat3fv(glm::mat3 value, const GLchar* name, GLboolean transpose = GL_FALSE) {
        this->use();

        glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, transpose, glm::value_ptr(value));

        this->unuse();
    }

    void setMat4fv(glm::mat4 value, const GLchar* name, GLboolean transpose = GL_FALSE) {
        this->use();

        glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, transpose, glm::value_ptr(value));

        this->unuse();
    }
};

