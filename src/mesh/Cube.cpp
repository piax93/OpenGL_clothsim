#include "Cube.hpp"
#include "../core/Transformation.hpp"

Cube::Cube(const glm::vec3& _center, float sideLen, const std::string& texture) 
        : DrawableMesh(texture), center(_center), halfsideColl(sideLen / 2.0f + COLL_EPS) {

    sideLen /= 2.0f;
    std::vector<Vertex> vertices;
    
    // Right face
    vertices.push_back(Vertex( sideLen,  sideLen,  sideLen, 0, 0, 1, 0, 0));
    vertices.push_back(Vertex( sideLen, -sideLen,  sideLen, 0, 1, 1, 0, 0));
    vertices.push_back(Vertex( sideLen,  sideLen, -sideLen, 1, 0, 1, 0, 0));
    vertices.push_back(Vertex( sideLen,  sideLen, -sideLen, 1, 0, 1, 0, 0));
    vertices.push_back(Vertex( sideLen, -sideLen,  sideLen, 0, 1, 1, 0, 0));
    vertices.push_back(Vertex( sideLen, -sideLen, -sideLen, 1, 1, 1, 0, 0));
    
    // Left face
    vertices.push_back(Vertex(-sideLen,  sideLen,  sideLen, 0, 0, -1, 0, 0));
    vertices.push_back(Vertex(-sideLen,  sideLen, -sideLen, 1, 0, -1, 0, 0));
    vertices.push_back(Vertex(-sideLen, -sideLen,  sideLen, 0, 1, -1, 0, 0));
    vertices.push_back(Vertex(-sideLen, -sideLen,  sideLen, 0, 1, -1, 0, 0));
    vertices.push_back(Vertex(-sideLen,  sideLen, -sideLen, 1, 0, -1, 0, 0));
    vertices.push_back(Vertex(-sideLen, -sideLen, -sideLen, 1, 1, -1, 0, 0));
    
    // Down face
    vertices.push_back(Vertex( sideLen, -sideLen,  sideLen, 1, 0, 0, -1, 0));
    vertices.push_back(Vertex(-sideLen, -sideLen,  sideLen, 0, 0, 0, -1, 0));    
    vertices.push_back(Vertex( sideLen, -sideLen, -sideLen, 1, 1, 0, -1, 0));
    vertices.push_back(Vertex( sideLen, -sideLen, -sideLen, 1, 1, 0, -1, 0));
    vertices.push_back(Vertex(-sideLen, -sideLen,  sideLen, 0, 0, 0, -1, 0));
    vertices.push_back(Vertex(-sideLen, -sideLen, -sideLen, 0, 1, 0, -1, 0));

    // Up face
    vertices.push_back(Vertex( sideLen,  sideLen,  sideLen, 1, 1, 0, 1, 0));
    vertices.push_back(Vertex( sideLen,  sideLen, -sideLen, 1, 0, 0, 1, 0));
    vertices.push_back(Vertex(-sideLen,  sideLen,  sideLen, 0, 1, 0, 1, 0));
    vertices.push_back(Vertex( sideLen,  sideLen, -sideLen, 1, 0, 0, 1, 0));
    vertices.push_back(Vertex(-sideLen,  sideLen, -sideLen, 0, 0, 0, 1, 0));
    vertices.push_back(Vertex(-sideLen,  sideLen,  sideLen, 0, 1, 0, 1, 0));

    // Front face
    vertices.push_back(Vertex( sideLen,  sideLen,  sideLen, 1, 0, 0, 0, 1));
    vertices.push_back(Vertex(-sideLen,  sideLen,  sideLen, 0, 0, 0, 0, 1));
    vertices.push_back(Vertex( sideLen, -sideLen,  sideLen, 1, 1, 0, 0, 1));
    vertices.push_back(Vertex( sideLen, -sideLen,  sideLen, 1, 1, 0, 0, 1));
    vertices.push_back(Vertex(-sideLen,  sideLen,  sideLen, 0, 0, 0, 0, 1));
    vertices.push_back(Vertex(-sideLen, -sideLen,  sideLen, 0, 1, 0, 0, 1));

    // Back face
    vertices.push_back(Vertex( sideLen,  sideLen, -sideLen, 1, 1, 0, 0, -1));
    vertices.push_back(Vertex( sideLen, -sideLen, -sideLen, 1, 0, 0, 0, -1));
    vertices.push_back(Vertex(-sideLen,  sideLen, -sideLen, 0, 1, 0, 0, -1));
    vertices.push_back(Vertex( sideLen, -sideLen, -sideLen, 1, 0, 0, 0, -1));
    vertices.push_back(Vertex(-sideLen, -sideLen, -sideLen, 0, 0, 0, 0, -1));
    vertices.push_back(Vertex(-sideLen,  sideLen, -sideLen, 0, 1, 0, 0, -1));

    setVertices(vertices);
}

void Cube::translateZ(float amount) {
    center.z += amount;
}

void Cube::draw(Shader& shader) {
    // Translate to sphere center
    Transformation::push();
    Transformation::reset();
    Transformation::translate(center);
    shader.transform();
    DrawableMesh::draw(shader);
    // Restore model matrix
    Transformation::pop();
    shader.transform();
}

void Cube::collide(Particle& p) const {
    glm::vec3 ray = p.v.position - center;
    if (glm::abs(ray.x) < halfsideColl && glm::abs(ray.y) < halfsideColl && glm::abs(ray.z) < halfsideColl) {
        ray = glm::normalize(ray) * halfsideColl * 2.0f;
        if (glm::abs(ray.x) > halfsideColl && ray.x != 0.f)
            ray *= halfsideColl / glm::abs(ray.x);
        if (glm::abs(ray.y) > halfsideColl && ray.y != 0.f)
            ray *= halfsideColl / glm::abs(ray.y);
        if (glm::abs(ray.z) > halfsideColl && ray.z != 0.f)
            ray *= halfsideColl / glm::abs(ray.z);
        p.resetPosition(center + ray);
    }
}