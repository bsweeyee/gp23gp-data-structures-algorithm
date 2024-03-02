#include "miniEngine.h"

MiniEngine engine;
double MiniEngine::mouse_screen_x = 0;
double MiniEngine::mouse_screen_y = 0;
double MiniEngine::mouse_screen_dx = 0;
double MiniEngine::mouse_screen_dy = 0;

MiniEngine::MiniEngine() {

}

MiniEngine::~MiniEngine() {
    delete window;
    delete renderer;
}

void MiniEngine::initialize(const char* title, int width, int height) {
    window = new gfx::Window();
    renderer = new gfx::Renderer();

    QueryPerformanceFrequency(&clock_freq);
	QueryPerformanceCounter(&last_frame_time);

    frame_count = 0;
    double x,y;
    glfwGetCursorPos(window->window, &x, &y);
    mouse_screen_x = x;
    mouse_screen_y = y;

    glfwSetKeyCallback(window->window, key_callback);
    glfwSetCursorPosCallback(window->window, cursor_position_callback);
    glfwSetMouseButtonCallback(window->window, mouse_button_callback);
}

bool MiniEngine::beginFrame() {
    LARGE_INTEGER frame_time;
	QueryPerformanceCounter(&frame_time);
	m_deltaTime = float(frame_time.QuadPart - last_frame_time.QuadPart) / clock_freq.QuadPart;
    last_frame_time = frame_time;
    
    frame_count++;
    
    glfwSwapBuffers(window->window);
    glfwPollEvents();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    return glfwWindowShouldClose(window->window);
}

void MiniEngine::close() {
    glfwSetWindowShouldClose(window->window, true);
}

float MiniEngine::deltaTime() {
    return m_deltaTime;
}

bool MiniEngine::keyDown(Key key) {
    InputState& state = key_states[(int)key];
	return state.down;
}

bool MiniEngine::keyPressed(Key key) {
    InputState& state = key_states[(int)key];
	return state.down && state.update_frame == frame_count;
}

bool MiniEngine::keyReleased(Key key) {
    InputState& state = key_states[(int)key];
	return !state.down && state.update_frame == frame_count;
}

bool MiniEngine::mouseDown(MouseButton button) {
    InputState& state = mouse_states[(int)button];
    return state.down;
}

bool MiniEngine::mousePressed(MouseButton button) {
    InputState& state = mouse_states[(int)button];
    return state.down && state.update_frame == frame_count;
}

bool MiniEngine::mouseReleased(MouseButton button) {
    InputState& state = mouse_states[(int)button];
    return !state.down && state.update_frame == frame_count;
}

void MiniEngine::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        InputState& state = key_states[key];
        state.set(true);
    } else if (action == GLFW_RELEASE) {
        InputState& state = key_states[key];
        state.set(false);
    }    
}

void MiniEngine::cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {    
    mouse_screen_dx = xpos - mouse_screen_x;
    mouse_screen_dy = ypos - mouse_screen_y;

    mouse_screen_x = xpos;
    mouse_screen_y = ypos;
}

void MiniEngine::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (action == GLFW_PRESS) {
        if (button == GLFW_MOUSE_BUTTON_LEFT) {
            InputState& state = mouse_states[(int)MouseButton::Left];
            state.set(true);
        }
        if (button == GLFW_MOUSE_BUTTON_RIGHT) {
            InputState& state = mouse_states[(int)MouseButton::Right];
            state.set(true);
        }
    }
    if (action == GLFW_RELEASE) {
        if (button == GLFW_MOUSE_BUTTON_LEFT) {
            InputState& state = mouse_states[(int)MouseButton::Left];
            state.set(false);
        }
        if (button == GLFW_MOUSE_BUTTON_RIGHT) {
            InputState& state = mouse_states[(int)MouseButton::Right];
            state.set(false);
        }
    }
}
    