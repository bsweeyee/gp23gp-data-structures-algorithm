#pragma once
#include "mesh.h"
#include "shader.h"

#define MAX_MESH 10
#define MAX_SHADER 10

namespace gfx {
    class Renderer {
    public:
        Mesh* meshes[MAX_MESH] = { nullptr };
        Shader* shaders[MAX_SHADER] = { nullptr };
        
        Renderer();           
        ~Renderer();

        void draw();
    };
}