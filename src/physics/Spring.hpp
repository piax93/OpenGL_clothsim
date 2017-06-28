#pragma once

#include "Particle.hpp"

#define K 20.0f              // Spring constant default

/**
 * Spring between particles
 */
class Spring {
private:

    Particle& a;            // Reference to the particle on one end of the spring
    Particle& b;            // Reference to the particle on other end of the spring
    const float restLen;    // Rest length of the spring
    const float k;          // String constant

public:

    /**
     * Attach spring
     * @param _a Reference to the particle on one end of the spring
     * @param _b Reference to the particle on other end of the spring
     */
    Spring(Particle& _a, Particle& _b, float k = K);

    /**
     * Apply physics
     */
    void update();

};