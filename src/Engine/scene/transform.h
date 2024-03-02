#pragma once
#include <glm.hpp>
#include <gtc/quaternion.hpp>

enum class ESpace {
    LOCAL,
    WORLD    
};

class Transform {
public:
    Transform* parent;
    glm::vec3 localPosition = glm::vec3(0.f,0.f,0.f);
    glm::quat quaternion = glm::quat(1.f,0.f,0.f,0.f);;
    glm::vec3 localScale = glm::vec3(1.f,1.f,1.f);;

    Transform();
    Transform(glm::vec3 in_position);
    Transform(glm::vec3 in_position, glm::quat in_quaternion);
    Transform(glm::vec3 in_position, glm::vec3 in_scale);
    Transform(glm::quat in_quaternion, glm::vec3 in_scale);
    Transform(glm::vec3 in_position, glm::quat in_quaternion, glm::vec3 in_scale);

    virtual void update();
    
    glm::vec3 translate(float dx, float dy, float dz, ESpace space = ESpace::LOCAL);            
    glm::quat rotate(float dx, float dy, float dz, ESpace space = ESpace::LOCAL); // euler angle rotation
    glm::quat rotate(glm::vec3 axis, float dA, ESpace space = ESpace::LOCAL); // axis angle rotation
    glm::vec3 scale(float dx, float dy, float dz);

    glm::vec3 worldPosition();
    glm::vec3 euler();
    glm::mat4 worldToLocalMatrix();
    glm::mat4 localToWorldMatrix();

    glm::vec3 up();
    glm::vec3 right();
    glm::vec3 forward();    
    
private:    
    glm::mat4 worldToLocal = glm::mat4(1.0f);
    glm::vec3 internal_euler;
};