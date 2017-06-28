#pragma once

#include "Particle.hpp"

#define COLL_EPS 0.053f

class Collider {
public:  
    
    /**
     * Check collision with particle
     */
    virtual void collide(Particle& p) const {}

};