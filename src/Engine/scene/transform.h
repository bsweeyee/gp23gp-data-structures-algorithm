#pragma once
#include <glm.hpp>
#include <gtc/quaternion.hpp>

enum class ESpace {
    LOCAL,
    WORLD    
};

class Transform {
public:
    static glm::vec3 worldUp;
    static glm::vec3 worldRight;
    static glm::vec3 worldForward;

    Transform* parent = nullptr;
    glm::vec3 worldPosition = glm::vec3(0.f,0.f,0.f);    
    glm::vec3 localPosition = glm::vec3(0.f,0.f,0.f);

    glm::vec3 eulerDegree = glm::vec3(0.f, 0.f, 0.f);

    glm::vec3 localScale = glm::vec3(1.f,1.f,1.f);;

    glm::vec3 right = glm::vec3(-1.f, 0.f, 0.f);
    glm::vec3 up = glm::vec3(0.f, 1.f, 0.f);
    glm::vec3 forward = glm::vec3(0.f, 0.f, 1.f);

    Transform(Transform* parent = nullptr);
    Transform(glm::vec3 in_position, Transform* parent = nullptr);
    Transform(glm::vec3 in_position, glm::quat in_quaternion, Transform* parent = nullptr);
    Transform(glm::vec3 in_position, glm::vec3 in_scale, Transform* parent = nullptr);
    Transform(glm::quat in_quaternion, glm::vec3 in_scale, Transform* parent = nullptr);
    Transform(glm::vec3 in_position, glm::quat in_quaternion, glm::vec3 in_scale, Transform* parent = nullptr);

    virtual void update();

    glm::mat4 localToWorldMatrix();
    glm::mat4 worldToLocalMatrix();
    
    glm::quat rotate(glm::vec3 axis, float dA); // axis angle rotation
    glm::quat rotate(glm::vec3 from, glm::vec3 to);
    glm::vec3 scale(float dx, float dy, float dz);
    
private:    
    glm::mat4 worldToLocal = glm::mat4(1);
    glm::mat4 localToWorld = glm::mat4(1);

    glm::vec3 internal_eulerDegree = glm::vec3(0.f,0.f,0.f);
    glm::vec3 internal_localPosition = glm::vec3(0.f,0.f,0.f);
    glm::vec3 internal_worldPosition = glm::vec3(0.f,0.f,0.f);
    
    glm::quat internal_quaternion = glm::quat(1.f,0.f,0.f,0.f);
    glm::quat delta_quaternion = glm::quat(0.f,0.f,0.f,0.f);

    glm::vec3 internal_scale = glm::vec3(1.f,1.f, 1.f);
};