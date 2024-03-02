#pragma once
#include <windows.h>
#include "gfx/renderer.h"
#include "gfx/window.h"
#include "input.h"

static unsigned int frame_count;
// Input stuff
struct InputState
{
	bool down = false;
    unsigned int update_frame = 0;    

	void set(bool new_down)
	{
		down = new_down;
        update_frame = frame_count;
	}
};

static InputState key_states[(int)Key::Count];
static InputState mouse_states[(int)MouseButton::Count];

class MiniEngine {
public:
    MiniEngine();
    ~MiniEngine();
    
    gfx::Window* window = nullptr;
    gfx::Renderer* renderer = nullptr;
    
    static double mouse_screen_x;
    static double mouse_screen_y;
    static double mouse_screen_dx;
    static double mouse_screen_dy;

    float m_deltaTime = 0.f;
    // Time keeping stuff
    LARGE_INTEGER clock_freq;
    LARGE_INTEGER last_frame_time;

    void initialize(const char* title, int width, int height);
    bool beginFrame();
    void close();
    float deltaTime();

    bool keyDown(Key key);
    bool keyPressed(Key key);
    bool keyReleased(Key key); 

    bool mouseDown(MouseButton button);
    bool mousePressed(MouseButton button);
    bool mouseReleased(MouseButton button);

private:
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);            
    static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
};
extern MiniEngine engine;