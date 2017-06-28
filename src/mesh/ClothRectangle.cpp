#include "ClothRectangle.hpp"
#include "../physics/World.hpp"

#define PBD_ITERATIONS 3

ClothRectangle::ClothRectangle(const glm::vec3& pos, float width, float height, 
    int hresolution, const std::string & textureFile) : DrawableMesh(textureFile) {

    // Evaluate horizontal and vertical subdivisions
    assert(hresolution > 0 && width > 0.0f && height > 0.0f);
    float xstep = width / hresolution;
    int vresolution = (int) glm::ceil(height / xstep);
    float ystep = height / vresolution;
    float ustep = 1.0f / hresolution;
    float vstep = 1.0f / vresolution;
    stripCount = vresolution++;
    stripLen = 2 * (++hresolution);
    float pmass = (width * height * 0.05f) / (vresolution * hresolution);

    // Create vertices
    vertices.reserve(vresolution * hresolution);
    particles.reserve(vresolution * hresolution);
    float starty = pos.y + height / 2;
    float startv = 1.0f;
    for (int i = 0; i < vresolution; i++) {
        float startx = pos.x - width / 2;
        float startu = 0.0f;
        for (int j = 0; j < hresolution; j++) {
            vertices.push_back(Vertex(startx, starty, 0.0f, startu, startv, 0.0f, 0.0f, 1.0f));
            particles.push_back(Particle(vertices.back(), pmass));
            startx += xstep;
            startu += ustep;
        }
        starty -= ystep;
        startv -= vstep;
    }

    // Create indices for triangle strips and setup springs
    int index;
    std::vector<int> indices;
    for (int i = 0; i < vresolution; i++) {
        for (int j = 0; j < hresolution; j++) {
            index = i * hresolution + j;
            if (i != vresolution - 1) {
                indices.push_back(index);
                indices.push_back(index + hresolution);
                springs.push_back(Spring(particles[index], particles[index + hresolution]));
                if (j != 0)
                    springs.push_back(Spring(particles[index], particles[index + hresolution - 1]));
                if (j != hresolution - 1)
                    springs.push_back(Spring(particles[index], particles[index + hresolution + 1]));
            }
            if (j != hresolution - 1) {
                springs.push_back(Spring(particles[index], particles[index + 1]));
            }
        }
    }

    setVertices(vertices, indices);
}

void ClothRectangle::fixCorner(CORNER corner, bool fixed) {
    switch (corner) {
        case TOP_LEFT:
            particles[0].setFixed(fixed);
            break;
        case TOP_RIGHT:
            particles[stripLen / 2 - 1].setFixed(fixed);
            break;
        case BOTTOM_LEFT:
            particles[stripCount * (stripLen / 2)].setFixed(fixed);
            break;
        case BOTTOM_RIGHT:
            particles.back().setFixed(fixed);
            break;
        default:
            break;
    }
}

void ClothRectangle::update(long dt) {

    // For each particle: reset normal, apply gravity, eval new position and check collisions
    float cdt = dt / 60.0f;
    World& world = World::getInstance();
    const std::vector<Collider*>& colliders = world.getColliders();
    glm::vec3 grav = world.getGravity() / (float)particles.size();
    for (auto it = particles.begin(); it != particles.end(); it++) {
        it->v.normal = glm::vec3(0);
        it->accelerate(grav);
        it->update(cdt);
        for (auto cit = colliders.begin(); cit != colliders.end(); cit++)
            (*cit)->collide(*it);
    }

    // Apply "spring" constraint
    for (int i = 0; i < PBD_ITERATIONS; i++) {
        for (auto it = springs.begin(); it != springs.end(); it++) {
            it->update();
        }
    }
    
    // Recompute vertex normals
    glm::vec3 norm;
    unsigned int hres = stripLen / 2, index;
    for (unsigned int i = 0; i < stripCount; i++) {
        for (unsigned int j = 0; j < hres - 1; j++) {
            index = i * hres + j;

            // Upper triangle of the quad
            norm = glm::cross(
                vertices[index + hres].position - vertices[index].position,
                vertices[index + 1].position - vertices[index].position
            );
            vertices[index].normal += norm;
            vertices[index + 1].normal += norm;
            vertices[index + hres].normal += norm;

            // Lower triangle of the quad
            norm = glm::cross(
                vertices[index + 1].position - vertices[index + hres + 1].position,
                vertices[index + hres].position - vertices[index + hres + 1].position
            );
            vertices[index + 1].normal += norm;
            vertices[index + hres].normal += norm;
            vertices[index + hres + 1].normal += norm;
        }
    }
    // Normalize normals
    for (auto it = vertices.begin(); it != vertices.end(); it++)
        it->normal = glm::normalize(it->normal);

    // Update vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexAB);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), NULL, GL_DYNAMIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(vertices[0]), vertices.data());
}

void ClothRectangle::draw(Shader& shader) {
    // Bind texture
    texture.bind(0);
    // Bind vertex array
    glBindVertexArray(vertexAO);
    // Draw rectangle using multiple triangle strips
    for(size_t i = 0; i < stripCount; i++)
        glDrawElements(GL_TRIANGLE_STRIP, stripLen, GL_UNSIGNED_INT, (void*)(i * stripLen * sizeof(int)));
    glBindVertexArray(0);
}