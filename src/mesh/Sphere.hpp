#pragma once

#include "DrawableMesh.hpp"
#include "../physics/Collider.hpp"


class Sphere : public DrawableMesh, public Collider {
private:

    glm::vec3 center;       // Center of the sphere
    float radius;           // Radius of the sphere
    float collision_radius; // Radius for collision detection
    int resolution;         // Vertical subdivision of the sphere

public:
    
    /**
     * Create a sphere mesh
     * @param _center Center of the sphere
     * @param _radius Radius of the sphere
     * @param resolution Vertical subdivision of the sphere
     * @param textureFile Path to texture image file
     */
    Sphere(const glm::vec3& _center, float _radius, int resolution, const std::string& textureFile);
 
    /**
     * Translate on the Z axis
     * @param amount Translation offset
     */
    void translateZ(float amount);

    virtual void draw(Shader& shader) override;

    virtual void collide(Particle& p) const override;

};