#include "Particle.hpp"

#define DAMP 0.2f

Particle::Particle(Vertex& _vertex, float _mass) 
    : v(_vertex), acceleration(0), mass(_mass), old_pos(_vertex.position), fixed(false) { }

void Particle::addForce(const glm::vec3& force) {
    acceleration += force / mass;
}

void Particle::accelerate(const glm::vec3 & acc) {
    acceleration += acc;
}

void Particle::offsetPosition(const glm::vec3& offset) {
    if (!fixed) v.position += offset;
}

void Particle::resetPosition(const glm::vec3& position) {
    v.position = position;
    old_pos = position;
}

void Particle::resetPosition() {
    v.position = old_pos;
}

void Particle::setFixed(bool _fixed) {
    fixed = _fixed;
}

bool Particle::isFixed() {
    return fixed;
}

void Particle::update(float dt) {
    if (!fixed) {
        glm::vec3 dx((v.position - old_pos) * (1 - DAMP) + acceleration * dt * dt);
        old_pos = v.position;
        v.position += dx;
    }
    acceleration = glm::vec3(0);
}