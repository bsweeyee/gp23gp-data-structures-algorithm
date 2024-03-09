#include "mesh.h"
#include "vertex.h"
#include <gtc/type_ptr.hpp>

namespace gfx {    
    Mesh::Mesh() {
    }

    void Mesh::init() {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertexSize * sizeof(Vertex), &vertices[0], GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

        // vertex positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    }

    void Mesh::draw(const Matrix4x4 clip, const Shader& shader, EDrawMode mode) {            
        // TODO: use EBO    
        int modelLoc = glGetUniformLocation(shader.shaderProgram, "clip");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, MatrixValue(clip));

        glUseProgram(shader.shaderProgram);
        
        glBindVertexArray(VAO);
        if (mode == EDrawMode::TRIANGLE) {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, 0);
        } else if (mode == EDrawMode::LINE) {
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glDrawArrays(GL_LINES, 0, 2);
        }
        // glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(0); // we reset the binded buffer
    }

    void Mesh::draw(Vertex* newVertices, const glm::mat4 clip, const Shader& shader, EDrawMode mode) {
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertexSize * sizeof(Vertex), &newVertices[0], GL_DYNAMIC_DRAW);

        draw(clip, shader, mode);
    }    
}