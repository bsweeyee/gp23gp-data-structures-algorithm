#pragma once
#include <glad.h>
#include <cstring>
#include "CIO.h"

namespace gfx {
    class Shader {
    public:
        unsigned int vertexShader; 
        unsigned int fragmentShader;
        unsigned int shaderProgram;

        Shader(const char* vs, const char* fs) {
            char buffer[2048];            

            CIO::readFile(vs, buffer);            
            const char* p = buffer;

            vertexShader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertexShader, 1, &p, NULL);
            glCompileShader(vertexShader);

            CIO::readFile(fs, buffer);            

            fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragmentShader, 1, &p, NULL);
            glCompileShader(fragmentShader);

            shaderProgram = glCreateProgram();
            glAttachShader(shaderProgram, vertexShader);
            glAttachShader(shaderProgram, fragmentShader);
            glLinkProgram(shaderProgram);

            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
        }
    };
}
