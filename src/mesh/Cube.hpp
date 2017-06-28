#pragma once

#include "DrawableMesh.hpp"
#include "../physics/Collider.hpp"

class Cube : public DrawableMesh, public Collider {
private:

    glm::vec3 center;                           // Center of the cube
    float halfsideColl;

public:

    Cube(const glm::vec3& _center, float sideLen, const std::string& texture);

    /**
    * Translate on the Z axis
    * @param amount Translation offset
    */
    void translateZ(float amount);

    virtual void draw(Shader& shader) override;

    virtual void collide(Particle& p) const override;

};