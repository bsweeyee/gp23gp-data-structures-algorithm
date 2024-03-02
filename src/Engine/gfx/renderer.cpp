#include "renderer.h"
#include "IO.h"

namespace gfx {
    Renderer::Renderer() {
        // TODO: load list of shader files here
        shaders[0] = new Shader("res/shader/default.vs", "res/shader/default.fs");
        
        // TODO: load list of meshes here
        meshes[0] = new Mesh();    
    }

    Renderer::~Renderer() {
        for(int i=0; i<MAX_SHADER; i++) {
            if (shaders[i] != nullptr) {
                delete shaders[i];
            }
        }
        for(int i=0; i<MAX_MESH; i++) {
            if (meshes[i] != nullptr) {
                delete meshes[i];
            }
        }        
    }

    void Renderer::draw() {                        
        for(int i=0; i<MAX_MESH; i++) {
            if (meshes[i] != nullptr) {
                meshes[i]->draw(glm::mat4(1), *shaders[0]);
            }
        }
    };
}
