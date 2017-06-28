#include "Sphere.hpp"
#include "../core/Transformation.hpp"
#include <glm/gtc/constants.hpp>

Sphere::Sphere(const glm::vec3& _center, float _radius, int _resolution, const std::string& textureFile) 
    : DrawableMesh(textureFile), center(_center), radius(_radius), resolution(_resolution), collision_radius(_radius + COLL_EPS) {
    
    assert(resolution > 0);

    float angleStep = glm::pi<float>() / resolution;
    float ustep = 0.5f / resolution;
    float vstep = 1.0f / resolution;
    resolution++;

    // Create vertices
    std::vector<Vertex> vertices;
    float teta = 0.0f;
    float v = 1.0f;
    for (int i = 0; i < resolution; i++) {
        float ro = 0.0f;
        float u = 0.0f;
        for (int j = 0; j < 2 * resolution; j++) {
            glm::vec3 pos(
                radius * sinf(teta) * cosf(ro),
                radius * cosf(teta),
                radius * sinf(teta) * sinf(ro)
            );
            glm::vec2 uv(u, v);
            vertices.push_back(Vertex(pos, uv, glm::normalize(pos)));
            ro += angleStep;
            u += ustep;
        }
        teta += angleStep;
        v -= vstep;
    }

    // Create indices for triangle strips
    std::vector<int> indices;
    for (int i = 0; i < resolution - 1; i++) {
        for (int j = 0; j < 2 * resolution; j++) {
            indices.push_back((i + 1) * 2 * resolution + j);
            indices.push_back(i * 2 * resolution + j);
        }
    }

    setVertices(vertices, indices);
}

void Sphere::translateZ(float amount) {
    center.z += amount;
}

void Sphere::draw(Shader& shader) {
    // Translate to sphere center
    Transformation::push();
    Transformation::reset();
    Transformation::translate(center);
    shader.transform();
    // Bind texture
    texture.bind(0);
    // Bind vertex array
    glBindVertexArray(vertexAO);
    // Draw sphere using multiple triangle strips
    int striplen = 4 * resolution;
    for (int i = 0; i < resolution - 1; i++)
        glDrawElements(GL_TRIANGLE_STRIP, striplen, GL_UNSIGNED_INT, (void*)(i * striplen * sizeof(int)));
    glBindVertexArray(0);
    // Restore model matrix
    Transformation::pop();
    shader.transform();
}

void Sphere::collide(Particle& p) const {
    glm::vec3 direction = p.v.position - center;
    if (glm::length(direction) < collision_radius) {
        p.resetPosition(glm::normalize(direction) * collision_radius + center);
    }
}