#include "camera.h"
#include "miniEngine.h"
#include <gtc/matrix_transform.hpp>

Camera::Camera(float width, float height) {
    transform.worldPosition = glm::vec3(0,0,-5);
    projection =  glm::perspective(glm::radians(45.0f), (float)width/(float)height, 0.1f, 100.0f);
}

void Camera::update() {
    if (engine.keyDown(Key::S)) {        
        glm::vec3 p = transform.forward * engine.deltaTime() * -5.f;        
        transform.worldPosition += p;
    }
    if (engine.keyDown(Key::W)) {
        glm::vec3 p = transform.forward * engine.deltaTime() * 5.f;        
        transform.worldPosition += p;        
    }
    if (engine.keyDown(Key::A)) {
        glm::vec3 p = transform.right * engine.deltaTime() * -5.f;        
        transform.worldPosition += p;        
    }
    if (engine.keyDown(Key::D)) {
        glm::vec3 p = transform.right * engine.deltaTime() * 5.f;        
        transform.worldPosition += p;      
    }

    if (engine.mouseDown(MouseButton::Right)) {
        transform.eulerDegree.y += MiniEngine::mouse_screen_dx * 5 * engine.deltaTime();                
    }    
}

void Camera::draw() {
    view = glm::lookAt(transform.worldPosition, transform.worldPosition + transform.forward ,transform.up);    
}