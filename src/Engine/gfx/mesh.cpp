#include "mesh.h"
#include "vertex.h"
#include <gtc/type_ptr.hpp>

namespace gfx {
    Mesh::Mesh() {
        // TODO: deserialize any mesh data here
        vertices[0] = Vertex(glm::vec3(-0.5f, -0.5f, 0.0f));                
        vertices[1] = Vertex(glm::vec3(0.5f, -0.5f, 0.0f));                
        vertices[2] = Vertex(glm::vec3(0.0f,  0.5f, 0.0f));                
                    
        vertexSize = 3;
        
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        // TODO: setup EBO

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glBufferData(GL_ARRAY_BUFFER, vertexSize * sizeof(Vertex), &vertices[0], GL_DYNAMIC_DRAW);

        // TODO: set up EBO

        // vertex positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    }

    void Mesh::draw(const glm::mat4 clip, Shader& shader) {            
        // TODO: use EBO

        int modelLoc = glGetUniformLocation(shader.shaderProgram, "clip");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(clip));

        glUseProgram(shader.shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
    }
}