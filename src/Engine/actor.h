#pragma once
#include "gfx/mesh.h"
#include "gfx/shader.h"
#include "scene/transform.h"
#include "camera.h"

class Transform;

class Actor {
public:
    Transform* transform;
    gfx::Mesh* mesh;

    Actor(gfx::Mesh* mesh);        
    Actor(Transform* transform, gfx::Mesh* mesh);        

    void update();
    void draw(Camera& camera, gfx::Shader* shader);    
};