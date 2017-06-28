#include "World.hpp"
#include "../core/Utils.hpp"
#include <SDL2/SDL.h>


World::World() : gravity(0) {
    cam = NULL;
    shader = NULL;
    time = 0;
}

void World::setupCamera(const glm::vec3& pos, float fov, const glm::ivec2& screenSize, float zNear, float zFar) {
    if (cam != NULL) delete cam;
    cam = new Camera(pos, fov, screenSize, zNear, zFar);
}

void World::setupShader(const std::string& name) {
    if (shader != NULL) delete shader;
    shader = new Shader(name);
}

void World::setupLight(const glm::vec3& position, float intensity) {
    if (light != NULL) delete light;
    light = new OmniLight(position, intensity);
}

#include <iostream>

void World::addMesh(DrawableMesh& mesh) {
    meshes.push_back(&mesh);
    if (dynamic_cast<Collider*>(&mesh) != nullptr)
        colliders.push_back(dynamic_cast<Collider*>(&mesh));
}

void World::setupGravity(const glm::vec3& _gravity) {
    gravity = _gravity;
}

void World::resetTime() {
    time = SDL_GetTicks();
}

glm::vec3 World::getGravity() const {
    return gravity;
}

const std::vector<Collider*>& World::getColliders() const {
    return colliders;
}

void World::update() {
    if (shader == NULL || light == NULL || cam == NULL)
        die("World not correctly set up");

    long dt = SDL_GetTicks() - time;
    time += dt;

    // Camera movements
    int mousedx, mousedy;
    const Uint8* keystate = SDL_GetKeyboardState(NULL);
    SDL_GetRelativeMouseState(&mousedx, &mousedy);
    cam->rotate(mousedx, mousedy);
    if (keystate[SDL_SCANCODE_W]) cam->moveZ(dt);
    if (keystate[SDL_SCANCODE_S]) cam->moveZ(-dt);
    if (keystate[SDL_SCANCODE_D]) cam->moveX(dt);
    if (keystate[SDL_SCANCODE_A]) cam->moveX(-dt);

    // Bind and update shader
    shader->bind();
    shader->update(*cam, *light);

    // Update and draw meshes
    for (auto it = meshes.begin(); it != meshes.end(); it++) {
        (*it)->update(dt);
        (*it)->draw(*shader);
    }
}

World::~World() {
    if (cam != NULL) delete cam;
    if (shader != NULL) delete shader;
    if (light != NULL) delete light;
    meshes.clear();
}