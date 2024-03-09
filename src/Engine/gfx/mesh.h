#pragma once
#include <glad.h>
#include <math.h>
#include <math/vector.h>
#include "vertex.h"
#include "shader.h"

#define MAX_VERTICES 2048
#define MAX_INDICES 2048

namespace gfx {
    enum class EDrawMode {
        LINE,
        TRIANGLE
    };

    struct Mesh {
        Vertex vertices[MAX_VERTICES];
        int indices[MAX_INDICES];

        int vertexSize = 0;
        int indicesSize = 0;

        unsigned int VBO, VAO, EBO;
        Mesh();
        virtual void init();
        virtual void draw(const glm::mat4 clip, const Shader& shader, EDrawMode mode = EDrawMode::TRIANGLE);        
        virtual void draw(Vertex* newVertices, const glm::mat4 clip, const Shader& shader, EDrawMode mode = EDrawMode::TRIANGLE);
    };

    struct Triangle : public Mesh {
        Triangle() : Mesh() {
            // TODO: deserialize any mesh data here
            vertices[0] = Vertex(Vector3(-0.5f, -0.5f, 0.0f));                
            vertices[1] = Vertex(Vector3(0.5f, -0.5f, 0.0f));                
            vertices[2] = Vertex(Vector3(0.0f,  0.5f, 0.0f));                        
            vertexSize = 3;

            indices[0] = 0;
            indices[1] = 1;
            indices[2] = 2;
            indicesSize = 3;

            init();
        }              
    };

    struct Rectangle : public Mesh {
        Rectangle() : Mesh() {
            vertices[0] = Vertex(Vector3(0.5f, 0.5f, 0.0f));                
            vertices[1] = Vertex(Vector3(0.5f, -0.5f, 0.0f));                
            vertices[2] = Vertex(Vector3(-0.5f,  -0.5f, 0.0f));                        
            vertices[3] = Vertex(Vector3(-0.5f,  0.5f, 0.0f));                                                            
            vertexSize = 4;

            indices[0] = 0;
            indices[1] = 1;
            indices[2] = 3;
            
            indices[3] = 1;
            indices[4] = 2;
            indices[5] = 3;

            indicesSize = 6;
            init();
        }
    };

    struct Circle : public Mesh {
        Circle() : Mesh() {
            int n = 30;
            // generate vertices
            float angle = TAU / n;                
            for(int i=0; i<n; i++) {
                float x = 0.5f * cosf(angle * i);
                float y = 0.5f * sinf(angle * i);
                vertices[i] = Vertex(Vector3(x, y, 0));
            }
            vertexSize = n;

            for (int i=0; i<n; i++) {
                int a = i*3;
                indices[a] = 0;
                indices[a+1] = i+1;
                indices[a+2] = i+2;
            }
            indicesSize = 3*n;                       
            init();
        }
    };

    struct Line : public Mesh {
        Line(Vertex start, Vertex end) : Mesh() {
            vertices[0] = start;
            vertices[1] = end;
            vertexSize = 2;
            init();
        }        
    };

    struct Cube : public Mesh {
        Cube() : Mesh() {
            vertices[0] = Vertex(Vector3(0.5f, 0.5f, 0.5f));
            vertices[1] = Vertex(Vector3(0.5f, -0.5f, 0.5f));
            vertices[2] = Vertex(Vector3(0.5f, -0.5f, -0.5f));
            vertices[3] = Vertex(Vector3(0.5f, 0.5f, -0.5f));
            
            vertices[4] = Vertex(Vector3(-0.5f, 0.5f, 0.5f));
            vertices[5] = Vertex(Vector3(-0.5f, -0.5f, 0.5f));
            vertices[6] = Vertex(Vector3(-0.5f, -0.5f, -0.5f));
            vertices[7] = Vertex(Vector3(-0.5f, 0.5f, -0.5f));
            
            vertexSize = 8;

            indices[0] = 0;
            indices[1] = 1;
            indices[2] = 2;
            
            indices[3] = 0;
            indices[4] = 2;
            indices[5] = 3;

            indices[6] = 3;
            indices[7] = 2;
            indices[8] = 6;

            indices[9] = 3;
            indices[10] = 6;
            indices[11] = 7;

            indices[12] = 0;
            indices[13] = 1;
            indices[14] = 5;

            indices[15] = 0;
            indices[16] = 5;
            indices[17] = 4;

            indices[18] = 4;
            indices[19] = 5;
            indices[20] = 6;

            indices[21] = 4;
            indices[22] = 6;
            indices[23] = 7;

            indicesSize = 24;
            init();            
        }
    };
}