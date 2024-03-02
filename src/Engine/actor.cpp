#include "actor.h"
#include "miniEngine.h"

Actor::Actor(gfx::Mesh* mesh)
    : transform(new Transform()), mesh(mesh) { }
Actor::Actor(Transform* transform, gfx::Mesh* mesh)
    : transform(transform), mesh(mesh) { }

void Actor::draw(Camera& camera, gfx::Shader* shader) {
    glm::mat4 clip = camera.projection * camera.view * transform->localToWorldMatrix();
    mesh->draw(clip, *shader);
}

void Actor::update() {    
    if (engine.keyDown(Key::E)) {
        transform->rotate(0, 0, 10 * engine.deltaTime());
    }
    if (engine.keyDown(Key::Q)) {
        transform->rotate(0, 0, -10 * engine.deltaTime());
    }

    transform->update();
}