#include "DrawableMesh.hpp"
#include "../core/Globals.hpp"
#include <numeric>

DrawableMesh::DrawableMesh(const std::vector<Vertex>& vertices, const std::vector<int>& indices, const std::string& textureFile)
    : texture(textureFile) {
    setVertices(vertices, indices);
}

DrawableMesh::DrawableMesh(const std::vector<Vertex>& vertices, const std::string& textureFile) : texture(textureFile) {
    setVertices(vertices);
}

DrawableMesh::DrawableMesh(const std::string& textureFile) : texture(textureFile), drawCount(0) {}

void DrawableMesh::setVertices(const std::vector<Vertex>& vertices, const std::vector<int>& indices) {
    drawCount = indices.size();
    // Setup vertex array handle
    glGenVertexArrays(1, &vertexAO);
    glBindVertexArray(vertexAO);
    // Load vertex buffer
    glGenBuffers(1, &vertexAB);
    glBindBuffer(GL_ARRAY_BUFFER, vertexAB);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), vertices.data(), GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(POSITION_ATTRIBUTE);
    glVertexAttribPointer(POSITION_ATTRIBUTE, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), NULL);
    glEnableVertexAttribArray(TEXTURE_UV_ATTRIBUTE);
    glVertexAttribPointer(TEXTURE_UV_ATTRIBUTE, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(NORMAL_ATTRIBUTE);
    glVertexAttribPointer(NORMAL_ATTRIBUTE, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void*)(5 * sizeof(float)));
    // Load index buffer
    glGenBuffers(1, &indexAB);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexAB);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), indices.data(), GL_STATIC_DRAW);
    glBindVertexArray(0);
}

void DrawableMesh::setVertices(const std::vector<Vertex>& vertices) {
    // Generate sequential indices
    std::vector<int> indices(vertices.size());
    std::iota(indices.begin(), indices.end(), 0);
    // Setup buffers
    setVertices(vertices, indices);
}

void DrawableMesh::draw(Shader& shader) {
    // Bind texture
    texture.bind(0);
    // Bind vertex array
    glBindVertexArray(vertexAO);
    // Draw elements from indices
    glDrawElements(GL_TRIANGLES, drawCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

DrawableMesh::~DrawableMesh() {
    // Clear vertex array
    glDeleteVertexArrays(1, &vertexAO);
}
