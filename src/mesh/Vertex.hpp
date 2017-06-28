#pragma once

#include <glm/glm.hpp>

/**
* Vertex in 3D space with texturing and lighting support
*/
struct Vertex {

    glm::vec3 position;     // Position of the vertex in 3D space
    glm::vec2 texCoord;     // UV texture coordinate
    glm::vec3 normal;       // Normal vector to the surface the vertex defines

    Vertex(float x, float y, float z, float u, float v, float nx, float ny, float nz)
        : position(x, y, z), texCoord(u, v), normal(glm::normalize(glm::vec3(nx, ny, nz))) {}
    Vertex(const glm::vec3& pos, const glm::vec2& uv, const glm::vec3& norm)
        : position(pos), texCoord(uv), normal(norm) {}

};