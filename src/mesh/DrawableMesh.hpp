#pragma once

#include <vector>
#include <string>
#include "../core/Shader.hpp"
#include "../core/Texture.hpp"
#include "Vertex.hpp"


/**
 * Generic mesh in 3D space
 */
class DrawableMesh {

protected:
    
    GLuint vertexAO;    // Vertex array handle
    GLuint vertexAB;    // Vertex array buffer handle
    GLuint indexAB;     // Index array buffer handle
    size_t drawCount;   // Number of indices
    Texture texture;    // Mesh texture
    
    /**
     * Setup mesh vertex buffer
     * @param vertices Array of vertices
     */
    void setVertices(const std::vector<Vertex>& vertices);
    
    /**
     * Setup mesh vertex and index buffers
     * @param vertices Array of vertices
     * @param indices Array of indices
     */
    void setVertices(const std::vector<Vertex>& vertices, const std::vector<int>& indices);
    
    /**
     * Private mesh constructor with textures only
     * @param textureFile Path to texture file
     */
    DrawableMesh(const std::string& textureFile);

public:

    /**
     * Generic mesh constructor
     * @param vertices Array of vertices
     * @param textureFile Path to texture file
     */
    DrawableMesh(const std::vector<Vertex>& vertices, const std::string& textureFile);
    
    /**
     * Generic mesh constructor
     * @param vertices Array of vertices
     * @param indices Array of indices to define draw order of the vertices
     * @param textureFile Path to texture file
     */
    DrawableMesh(const std::vector<Vertex>& vertices, const std::vector<int>& indices, const std::string& textureFile);
    
    /**
     * Draw the mesh (if not overridden draws triangles)
     * @param shader Shader program to pass transformations to
     */
    virtual void draw(Shader& shader);
    
    /**
     * Update the mesh components
     * @param dt Time interval
     */
    virtual void update(long dt) {}
    
    virtual ~DrawableMesh();

};
