#pragma once

#include "../mesh/Vertex.hpp"

#define MASS 6.f

/**
 * Physics particle
 */
class Particle {
private:

    bool fixed;             // True if particle cannot move
    float mass;             // Mass of the particle
    glm::vec3 acceleration; // Acceleration acting on the particle
    glm::vec3 old_pos;      // Position on previous timestep for Verlet integration

public:

    Vertex& v;              // Reference to the vertex representing the particle in 3D space

    /**
     * Create a particle
     * @param _vertex Reference to a vertex in 3D space
     */
    Particle(Vertex& _vertex, float mass = MASS);

    /**
     * Apply a force on the particle
     * @param force Force vector
     */
    void addForce(const glm::vec3& force);

    /**
     * Apply acceleration to the particle
     * @param acc Acceleration vector
     */
    void accelerate(const glm::vec3& acc);

    /**
     * If movable, change the position of the particle
     * @param offset Movement
     */
    void offsetPosition(const glm::vec3& offset);

    /**
     * Resets position
     * @param position Position to set the particle to
     */
    void resetPosition(const glm::vec3& position);

    /**
     * Resets position to previous position
     */
    void resetPosition();

    /**
     * Set if the particle is allowed to move
     * @param _fixed True if particle cannot move
     */
    void setFixed(bool _fixed);

    /**
     * Returns true if the particle is fixed
     */
    bool isFixed();

    /**
     * Apply physics
     */
    void update(float dt);

};