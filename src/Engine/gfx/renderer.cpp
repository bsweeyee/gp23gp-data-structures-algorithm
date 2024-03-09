#include "renderer.h"
#include "IO.h"

namespace gfx {

    Mesh* Renderer::meshes[MAX_MESH] = { nullptr };
    Shader* Renderer::shaders[MAX_SHADER] = { nullptr };    
    Camera* Renderer::camera = nullptr;

    Renderer::Renderer(Camera* camera) {        
        Renderer::camera = camera;
        // TODO: load list of shader files here
        shaders[0] = new Shader("res/shader/default.vs", "res/shader/default.fs");
        
        // TODO: load list of meshes here
        meshes[0] = new Rectangle();
        meshes[1] = new Triangle();
        meshes[2] = new Circle();
        meshes[3] = new Line(Vector3(0.f, 0.f, 0.f), Vector3(0.f, 1.f, 0.f));    
        meshes[4] = new Cube();    
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
}
