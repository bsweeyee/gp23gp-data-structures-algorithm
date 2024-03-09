#pragma once
#include <gtc/type_ptr.hpp>
#include <glm.hpp>

typedef  glm::vec3 Vector3;
typedef glm::vec4 Vector4;
typedef glm::mat4 Matrix4x4;

#define MatrixValue glm::value_ptr
#define VectorLerp glm::mix
#define TAU 6.28318530718f