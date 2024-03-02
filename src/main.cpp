#include "Engine/miniEngine.h"
#include "Engine/actor.h"
#include "Engine/camera.h"

#define MAX_ACTORS 100
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main() 
{
    engine.initialize("MiniEngine", WINDOW_WIDTH, WINDOW_HEIGHT);

    Camera camera(WINDOW_WIDTH, WINDOW_HEIGHT);

    Actor* actors[MAX_ACTORS] = { nullptr };
    actors[0] = new Actor(engine.renderer->meshes[0]);    

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

        // TODO: send camera matrix here
        for(int i=0; i<MAX_ACTORS; i++) {
            if (actors[i] != nullptr) {
                actors[i]->draw(camera, engine.renderer->shaders[0]);
            }
        }

        camera.update();

        MiniEngine::mouse_screen_dx = 0;
        MiniEngine::mouse_screen_dy = 0;
    }

    return 0;
}