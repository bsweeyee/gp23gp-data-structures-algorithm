#pragma once
#include <glad.h>
#include "vertex.h"
#include "shader.h"

#define MAX_VERTICES 2048


namespace gfx {    
    struct Mesh {
        Vertex vertices[MAX_VERTICES];
        int vertexSize = 0;

        unsigned int VBO, VAO;
        Mesh();
        void draw(const glm::mat4 clip, Shader& shader);
    };
}