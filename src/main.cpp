#include "physics/World.hpp"
#include "core/Display.hpp"
#include "mesh/ClothRectangle.hpp"
#include "mesh/Sphere.hpp"
#include "mesh/Cube.hpp"

#define COLL_MESH 0         // 0 for sphere, 1 for cube

int main(int argc, char* args[]) {
    // Create window
    Display display(640, 360, "Cloth simulation");
    // Setup world
    World& world = World::getInstance();
    world.setupCamera(glm::vec3(0, 0, 3), 70.0f, display.screenSize(), 0.01f, 1000.0f);
    world.setupLight(glm::vec3(-1.f, 1.f, 2.5f), 60.0f);
    world.setupShader("basic");
    world.setupGravity(glm::vec3(0.0f, -3.0f, 0.0f));
    // Create meshes and add them to the world
    ClothRectangle cloth(glm::vec3(0), 1.5, 1, 16,"res/flag.png");
    cloth.fixCorner(ClothRectangle::CORNER::TOP_LEFT);
    cloth.fixCorner(ClothRectangle::CORNER::TOP_RIGHT);
    Sphere sphere(glm::vec3(0, -0.3f, 1.4f), 0.3f, 50, "res/flag.png");
    Cube cube(glm::vec3(0, -0.4, 1.4f), 0.5f, "res/ccube.png");
    world.addMesh(cloth);
    if (COLL_MESH) world.addMesh(cube);
    else world.addMesh(sphere);

    // Start event loop
    world.resetTime();
    float angle = 0.0f;
    while(display.update()) {
        display.clear(0, 0, 0);
        world.update();
        sphere.translateZ(-0.01f * glm::sign(glm::sin(angle)));
        cube.translateZ(-0.01f * glm::sign(glm::sin(angle)));
        angle += 0.01f;
    }

    return 0;
}