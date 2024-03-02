#include "Transform.h"

Transform::Transform()
    : localPosition(glm::vec3(0.f,0.f,0.f)), quaternion(glm::quat(1.f,0.f,0.f,0.f)), localScale(glm::vec3(1.f,1.f,1.f)) 
{ 
    glm::mat4 T = glm::translate(glm::mat4(1), localPosition);
    glm::mat4 R = glm::mat4_cast(quaternion);
    glm::mat4 S = glm::scale(glm::mat4(1), localScale);

    worldToLocal = T*R*S; // TODO: accout for parent
    internal_euler = glm::degrees(glm::eulerAngles(quaternion));
}
Transform::Transform(glm::vec3 in_position)
    : localPosition(in_position), quaternion(glm::quat(1.f,0.f,0.f,0.f)), localScale(glm::vec3(1.f,1.f,1.f))
{ 
    glm::mat4 T = glm::translate(glm::mat4(1), localPosition);
    glm::mat4 R = glm::mat4_cast(quaternion);
    glm::mat4 S = glm::scale(glm::mat4(1), localScale);

    worldToLocal = T*R*S;
    internal_euler = glm::degrees(glm::eulerAngles(quaternion));
}
Transform::Transform(glm::vec3 in_position, glm::quat in_quaternion)
    : localPosition(in_position), quaternion(in_quaternion), localScale(glm::vec3(1.f,1.f,1.f))
{
    glm::mat4 T = glm::translate(glm::mat4(1), localPosition);
    glm::mat4 R = glm::mat4_cast(quaternion);
    glm::mat4 S = glm::scale(glm::mat4(1), localScale);

    worldToLocal = T*R*S;
    internal_euler = glm::degrees(glm::eulerAngles(quaternion));
}
Transform::Transform(glm::vec3 in_position, glm::vec3 in_scale)
    : localPosition(in_position), quaternion(glm::quat(1.f,0.f,0.f,0.f)), localScale(in_scale)
{
    glm::mat4 T = glm::translate(glm::mat4(1), localPosition);
    glm::mat4 R = glm::mat4_cast(quaternion);
    glm::mat4 S = glm::scale(glm::mat4(1), localScale);

    worldToLocal = T*R*S;
    internal_euler = glm::degrees(glm::eulerAngles(quaternion));
}
Transform::Transform(glm::quat in_quaternion, glm::vec3 in_scale)
    : localPosition(glm::vec3(0.f,0.f,0.f)), quaternion(in_quaternion), localScale(in_scale)
{
    glm::mat4 T = glm::translate(glm::mat4(1), localPosition);
    glm::mat4 R = glm::mat4_cast(quaternion);
    glm::mat4 S = glm::scale(glm::mat4(1), localScale);

    worldToLocal = T*R*S;
    internal_euler = glm::degrees(glm::eulerAngles(quaternion));
}
Transform::Transform(glm::vec3 in_position, glm::quat in_quaternion, glm::vec3 in_scale)
    : localPosition(in_position), quaternion(in_quaternion), localScale(in_scale)
{
    glm::mat4 T = glm::translate(glm::mat4(1), localPosition);
    glm::mat4 R = glm::mat4_cast(quaternion);
    glm::mat4 S = glm::scale(glm::mat4(1), localScale);

    worldToLocal = T*R*S;
    internal_euler = glm::degrees(glm::eulerAngles(quaternion));
}

void Transform::update() {
    // TODO: convert public euler and local position here
    // glm::vec3 v = glm::vec3(localPosition);
    // v = glm::inverse(trs) * glm::vec4(v, 0);

    glm::mat4 T = glm::translate(glm::mat4(1), localPosition);
    glm::mat4 R = glm::mat4_cast(quaternion);
    glm::mat4 S = glm::scale(glm::mat4(1), localScale);
    
    worldToLocal = T*R*S;
    
    internal_euler = glm::degrees(glm::eulerAngles(quaternion));
}

glm::vec3 Transform::worldPosition() {
    return glm::vec3(localToWorldMatrix() * glm::vec4(localPosition, 0));
}

glm::vec3 Transform::euler() {
    return internal_euler;
}
glm::mat4 Transform::worldToLocalMatrix() {
    return worldToLocal;
}
glm::mat4 Transform::localToWorldMatrix() {
    return glm::inverse(worldToLocal);
}

glm::vec3 Transform::up()
{
    return (glm::vec3) (localToWorldMatrix() * glm::vec4(0, 1, 0, 0));
}
glm::vec3 Transform::right()
{
    return (glm::vec3) (localToWorldMatrix() * glm::vec4(1, 0, 0, 0));
}
glm::vec3 Transform::forward()
{
    return (glm::vec3) (localToWorldMatrix() * glm::vec4(0, 0, 1, 0));
}

glm::vec3 Transform::translate(float dx, float dy, float dz, ESpace space) {
    // if v is in world space, then we assume v is a world vector, so we can directly add it to world position
    glm::vec3 v = glm::vec3(-dx, dy, dz);    

    // if v is in local space, then we assume v is local so we do a local -> world transform to get the world vector, then add to world position
    if (space == ESpace::LOCAL)
    {
        v = localToWorldMatrix() * glm::vec4(v, 0); // TODO: multiply by parent transform for correct local space translation
    }

    localPosition += v;     

    return localPosition;

}            
glm::quat Transform::rotate(float dx, float dy, float dz, ESpace space) {
    // assumes input axes is in local space
    glm::vec3 zAxis = glm::vec3(0, 0, 1);
    glm::vec3 xAxis = glm::vec3(1, 0, 0);
    glm::vec3 yAxis = glm::vec3(0, 1, 0);    
    
    if (space == ESpace::WORLD)
    {                                                    
        // find axis relative to world space
        zAxis = glm::inverse(worldToLocal) * glm::vec4(0, 0, 1, 0);
        xAxis = glm::inverse(worldToLocal) * glm::vec4(1, 0, 0, 0);
        yAxis = glm::inverse(worldToLocal) * glm::vec4(0, 1, 0, 0);            
    }

    glm::quat zRot = glm::rotate(glm::mat4(1.0f), glm::radians(dz), zAxis);
    glm::quat xRot = glm::rotate(glm::mat4(1.0f), glm::radians(dx), xAxis);
    glm::quat yRot = glm::rotate(glm::mat4(1.0f), glm::radians(dy), yAxis);

    quaternion *= yRot * xRot * zRot;    

    return quaternion;

} // euler angle rotation
glm::quat Transform::rotate(glm::vec3 axis, float dA, ESpace space){
    if (space == ESpace::LOCAL)
    {
        axis = worldToLocal * glm::vec4(axis, 0);                
    }    
    
    glm::quat out = glm::angleAxis(dA, axis);

    quaternion = out * quaternion;

    return quaternion;

} // axis angle rotation
glm::vec3 Transform::scale(float dx, float dy, float dz) {
    localScale += glm::vec3(dx, dy, dz);
   
    return localScale;
}