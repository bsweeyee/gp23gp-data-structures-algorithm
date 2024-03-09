#include "Transform.h"
#include <cstdio>

glm::vec3 Transform::worldUp = glm::vec3(0, 1, 0);
glm::vec3 Transform::worldRight = glm::vec3(-1, 0, 0);
glm::vec3 Transform::worldForward = glm::vec3(0, 0, 1);

Transform::Transform(Transform* parent)
    : Transform(glm::vec3(0.f,0.f,0.f), glm::quat(1.f,0.f,0.f,0.f), glm::vec3(1.f,1.f,1.f), parent) {}
Transform::Transform(glm::vec3 in_position, Transform* parent)
    :  Transform(in_position, glm::quat(1.f,0.f,0.f,0.f), glm::vec3(1.f,1.f,1.f), parent) { }
Transform::Transform(glm::vec3 in_position, glm::quat in_quaternion, Transform* parent)
    : Transform(in_position, in_quaternion, glm::vec3(1.f,1.f,1.f), parent) { }
Transform::Transform(glm::vec3 in_position, glm::vec3 in_scale, Transform* parent)
    : Transform(in_position, glm::quat(1.f,0.f,0.f,0.f), in_scale, parent) { }
Transform::Transform(glm::quat in_quaternion, glm::vec3 in_scale, Transform* parent)
    : Transform(glm::vec3(0.f,0.f,0.f), in_quaternion, in_scale, parent) { }
Transform::Transform(glm::vec3 in_position, glm::quat in_quaternion, glm::vec3 in_scale, Transform* parent)
    : localPosition(in_position), internal_quaternion(in_quaternion), localScale(in_scale)
{
    this->parent = parent;
    glm::mat4 tParent = glm::mat4(1);      
    if (this->parent != nullptr) {
        tParent = parent->worldToLocal;
    }

    // glm::vec3 dLocalPos = in_position - localPosition;
    // glm::vec3 dWorldPos = worldPosition - internal_worldPosition;

    glm::mat4 T = glm::translate(tParent, in_position);
    glm::mat4 R = glm::mat4_cast(in_quaternion);
    glm::mat4 S = glm::inverse(glm::scale(glm::mat4(1), in_scale));

    worldToLocal = S*R*T* worldToLocal; // TODO: accout for parent
    localToWorld = glm::inverse(worldToLocal);
    
    up = glm::vec3(worldToLocal * glm::vec4(Transform::worldUp, 0));
    right = glm::vec3(worldToLocal * glm::vec4(Transform::worldRight, 0));
    forward = glm::vec3(worldToLocal * glm::vec4(Transform::worldForward, 0));    
    
    worldPosition = localToWorld * glm::vec4(localPosition, 1);

    internal_localPosition = localPosition;
    internal_worldPosition = worldPosition;
    eulerDegree += glm::degrees(glm::eulerAngles(in_quaternion));
    internal_eulerDegree = eulerDegree;            
}

void Transform::update() {    
    // transform local to world pos using up, right forward values
    glm::mat4 tParent = glm::mat4(1);      
    if (parent != nullptr) {
        tParent = parent->worldToLocal;
    }

    glm::vec3 dLocalPos = localPosition - internal_localPosition;
    glm::vec3 dWorldPos = worldPosition - internal_worldPosition;        

    glm::vec3 dEuler = eulerDegree - internal_eulerDegree;
    glm::quat dEulerQuat = glm::quat(glm::radians(dEuler));    

    glm::vec3 dScale = localScale - internal_scale;

    glm::mat4 dT = glm::translate(glm::mat4(1), dWorldPos) * glm::translate(tParent, dLocalPos);
    glm::mat4 dR = glm::mat4_cast(glm::cross(delta_quaternion, dEulerQuat));
    // TODO: fix scaling issue
    glm::mat4 dS = glm::inverse(glm::scale(glm::mat4(1), localScale));

    worldToLocal = dS*dR*dT* worldToLocal; // TODO: accout for parent    
    localToWorld = glm::inverse(worldToLocal);

    up = glm::vec3(worldToLocal * glm::vec4(Transform::worldUp, 0));
    right = glm::vec3(worldToLocal * glm::vec4(Transform::worldRight, 0));
    forward = glm::vec3(worldToLocal * glm::vec4(Transform::worldForward, 0));        

    internal_localPosition = localPosition;
    internal_worldPosition = worldPosition;
    eulerDegree += glm::degrees(glm::eulerAngles(delta_quaternion));
    internal_eulerDegree = eulerDegree;
    internal_scale = localScale;        

    internal_quaternion =  glm::cross(internal_quaternion, delta_quaternion);
    delta_quaternion = glm::quat(1.f,0.f,0.f,0.f);    
}

glm::mat4 Transform::localToWorldMatrix() {
    return localToWorld;
}

glm::mat4 Transform::worldToLocalMatrix() {
    return worldToLocal;
}

// TODO: find a way to store 
glm::quat Transform::rotate(glm::vec3 axis, float dA){
    delta_quaternion = glm::angleAxis(dA, axis);
    return delta_quaternion;

} // axis angle rotation

glm::quat Transform::rotate(glm::vec3 from, glm::vec3 to) {
    glm::vec3 axis = glm::cross(from, to);
    float angle = glm::degrees(acos(glm::dot(glm::normalize(from), glm::normalize(to))));
    return rotate(axis, angle);
}

glm::vec3 Transform::scale(float dx, float dy, float dz) {
    localScale += glm::vec3(dx, dy, dz);
   
    return localScale;
}