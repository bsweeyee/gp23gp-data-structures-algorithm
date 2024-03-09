#include "Engine/miniEngine.h"
#include "Engine/actor.h"
#include "Engine/gfx/renderer.h"
#include "Engine/camera.h"
#include "Engine/math/vector.h"

#define MAX_ACTORS 100
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600 

int main() 
{
    engine.initialize("MiniEngine", WINDOW_WIDTH, WINDOW_HEIGHT);

    Actor* actors[MAX_ACTORS] = { nullptr };
    Camera camera(WINDOW_WIDTH, WINDOW_HEIGHT);
    gfx::Renderer render(&camera);

    actors[0] = new Actor(gfx::Renderer::meshes[4]);
    
    while(!engine.beginFrame())
    {
        if (engine.keyPressed(Key::Escape)) {
            engine.close();
        }

        for(int i=0; i<MAX_ACTORS; i++) {
            if (actors[i] != nullptr) {
                actors[i]->update();
            }
        }

        // update logic and transform
        camera.update();        
        camera.transform.update();        

        for(int i=0; i<MAX_ACTORS; i++) {
            if (actors[i] != nullptr) {
                actors[i]->draw(camera, gfx::Renderer::shaders[0]);
            }
        }

        // TOOD: draw grid
        for(int i=-5; i<6; i++) {        
            gfx::Renderer::DrawLine(Vector3(i, -0.5f, -5), Vector3(i, -0.5f, 5));        
        }
        for (int j=-5; j<6; j++) {
            gfx::Renderer::DrawLine(Vector3(-5, -0.5f, j), Vector3(5, -0.5f, j));                                      
        }        

        // draw
        camera.draw();

        MiniEngine::mouse_screen_dx = 0;
        MiniEngine::mouse_screen_dy = 0;
    }

    return 0;
}