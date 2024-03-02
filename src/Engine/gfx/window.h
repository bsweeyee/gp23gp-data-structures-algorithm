#pragma once
#include <iostream>
#include <glad.h> 
#include <glfw3.h>

namespace gfx {
    struct Window {
        GLFWwindow* window;

        Window(); 
        ~Window();
    };
}