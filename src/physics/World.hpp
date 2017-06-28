#pragma once

#include <map>
#include <vector>
#include "Collider.hpp"
#include "../core/Shader.hpp"
#include "../core/Camera.hpp"
#include "../mesh/DrawableMesh.hpp"

/**
 * World container
 */
class World {

private:

    long time;                              // Current SDL time
    Camera* cam;                            // Camera
    Shader* shader;                         // Shader
    OmniLight* light;                       // Light
    glm::vec3 gravity;                      // Gravity acceleration
    std::vector<DrawableMesh*> meshes;      // Objects in the world
    std::vector<Collider*> colliders;       // Objects in the world with Collider interface
    
    /**
     * Private world constructor
     */
    World();

    /**
     * Private world destructor
     */
    virtual ~World();

public:

    /**
     * Get world instance (lazy singleton implementation)
     */
    static World& getInstance() { static World w; return w; }
    
    /**
     * Setup camera for the scene
     * @param pos Position in 3D space
     * @param fov Vertical field of view
     * @param screenSize Size of the viewport in pixels
     * @param zNear Distance of the near plane
     * @param zFar Distance of the far plane
     */
    void setupCamera(const glm::vec3& pos, float fov, const glm::ivec2& screenSize, float zNear, float zFar);
    
    /**
     * Setup omnilight for the scene
     * @param position 3D position of the light
     * @param intensity Intensity of the light
     */
    void setupLight(const glm::vec3& position, float intensity);
    
    /**
     * Setup shader
     * @param name Name of the shader
     */
    void setupShader(const std::string& name);
    
    /**
     * Add object to the world
     * @param mesh Object to add (this memory entry must be permanent through all program execution)
     */
    void addMesh(DrawableMesh& mesh);

    /**
     * Setup world gravity
     * @param gravity Gravity vector
     */
    void setupGravity(const glm::vec3& gravity);

    /**
     * Reset world timer
     */
    void resetTime();

    /**
     * Get gravity vector
     */
    glm::vec3 getGravity() const;

    /**
     * Get colliders present in the world
     */
    const std::vector<Collider*>& getColliders() const;
    
    /**
     * Get input and update objects
     */
    void update();

};