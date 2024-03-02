#pragma once
#include <glm.hpp>

namespace gfx {
    struct Vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoords;

        Vertex() {}
        Vertex(glm::vec3 position)
            : position(position), normal(glm::vec3(0.f,0.f,0.f)), texCoords(glm::vec2(0.f,0.f)) {}
        Vertex(glm::vec3 position, glm::vec3 normal, glm::vec2 texCoords)
            : position(position), normal(normal), texCoords(texCoords) { }
    };
}
