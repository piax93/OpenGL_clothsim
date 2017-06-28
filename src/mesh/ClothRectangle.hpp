#pragma once

#include "DrawableMesh.hpp"
#include "../physics/Spring.hpp"


class ClothRectangle : public DrawableMesh {
private:

    size_t stripLen;                    // Number of indices in a triangle strip
    size_t stripCount;                  // Number of triangle stips
    std::vector<Vertex> vertices;       // Vertices in 3D space (for drawing)
    std::vector<Particle> particles;    // Particles for physics
    std::vector<Spring> springs;        // Springs joining the particles

public:

    /**
     * Create a rectangular cloth mesh.
     * @param position Position of the center is 3D space
     * @param width Width of the cloth
     * @param height Height of the cloth
     * @param hresolution Horizontal resolution of the cloth (number of quads subdividing the width)
     * @param textureFile Path to image file containing the texture
     */    
    ClothRectangle(const glm::vec3& position, float width, float height, int hresolution, const std::string& textureFile);
    
    /**
     * IDs for the corners of the cloth
     */
    enum CORNER { TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT };

    /**
     * Fix a corner of the cloth
     * @param corner Value from CORNER enum
     * @param fixed False to unfix the corner
     */
    void fixCorner(CORNER corner, bool fixed = true);

    virtual void update(long dt) override;
    
    virtual void draw(Shader& shader) override;

};