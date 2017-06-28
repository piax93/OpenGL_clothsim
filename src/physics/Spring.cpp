#include "Spring.hpp"


Spring::Spring(Particle& _a, Particle& _b, float _k)
    : a(_a), b(_b), k(_k), restLen(glm::distance(a.v.position, b.v.position)) {}


void Spring::update() {
    glm::vec3 direction = b.v.position - a.v.position;
    
    // Normal spring physics (unstable)
    // glm::vec3 force = -k * (restLen - glm::length(direction)) * glm::normalize(direction);
    // a.addForce(force);
    // b.addForce(-force);

    // Non-elastic constraint
    glm::vec3 correction = direction * (1 - restLen / glm::length(direction));
    if (!(a.isFixed() || b.isFixed())) correction *= 0.5f;
    a.offsetPosition(correction);
    b.offsetPosition(-correction);
}