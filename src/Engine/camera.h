#pragma once
#include <glm.hpp>
#include "scene/transform.h"

class Camera {
public:
    Camera(float width, float height);

    Transform transform = Transform();
    glm::mat4 view = glm::mat4(1);    
    glm::mat4 projection = glm::mat4(1);

    void update();
private:

};