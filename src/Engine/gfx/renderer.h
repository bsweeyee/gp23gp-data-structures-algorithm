#pragma once
#include "mesh.h"
#include "shader.h"
#include "camera.h"
#include <scene/transform.h>

#define MAX_MESH 100
#define MAX_SHADER 100

namespace gfx {
    class Renderer {
    public:
        static Mesh* meshes[MAX_MESH];
        static Shader* shaders[MAX_SHADER];
        static Camera* camera;

        Renderer(Camera* camera);           
        ~Renderer();

        static void DrawTriangle(const Vector3& position) {
            Transform t(position);            
            Matrix4x4 proj = camera->projection;
            Matrix4x4 view = camera->view;
            Matrix4x4 model = t.localToWorldMatrix();
            Matrix4x4 clip = proj * view * model;
            meshes[1]->draw(clip, (*shaders[0]));                                                
        };

        static void DrawRectangle(const Vector3& position) {
            Transform t(position);                        
            t.update();
            
            Matrix4x4 proj = camera->projection;
            Matrix4x4 view = camera->view;
            Matrix4x4 model = t.localToWorldMatrix();
            Matrix4x4 clip = proj * view * model;
            meshes[0]->draw(clip, (*shaders[0]));                                                
        };

        static void DrawCircle(const Vector3& position) {
            Transform t(position);            
            Matrix4x4 proj = camera->projection;
            Matrix4x4 view = camera->view;
            Matrix4x4 model = t.localToWorldMatrix();
            Matrix4x4 clip = proj * view * model;
            meshes[2]->draw(clip, (*shaders[0]));  
        }

        // TODO: fix end position for line rendering
        static void DrawLine(const Vector3& start, const Vector3& end) {            
            // Transform t(start);            

            Matrix4x4 proj = camera->projection;
            Matrix4x4 view = camera->view;
            // Matrix4x4 model = t.localToWorldMatrix();
            Matrix4x4 clip = proj * view * Matrix4x4(1);
            
            Vertex nVertices[2];
            // nVertices[0] = Vector3(clip * Vector4(start, 1));
            // nVertices[1] = Vector3(clip * Vector4(end, 1));
            nVertices[0] = start;
            nVertices[1] = end;

            meshes[3]->draw(nVertices, clip, (*shaders[0]), gfx::EDrawMode::LINE);    
        }

        static void DrawCube(const Vector3& position, float size) {
            Transform t(position, Vector3(size, size, size));            
            Matrix4x4 proj = camera->projection;
            Matrix4x4 view = camera->view;
            Matrix4x4 model = t.localToWorldMatrix();
            Matrix4x4 clip = proj * view * model;

            meshes[4]->draw(clip, (*shaders[0]));  
        }

        static void DrawSphere(const Vector3& position) {
        }
    };
}