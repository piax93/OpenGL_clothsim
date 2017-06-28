#pragma once

#include <string>
#include <GL/glew.h>

/**
 * Texture from image file
 */
class Texture {

private:

    GLuint texture;     // OpenGL handle to texture

public:

    /**
     * Texture constructor
     * @param filename Path to texture image file
     */
    Texture(const std::string& filename);

    /**
     * Bind texture to unit
     * @param unit Texture unit
     */
    void bind(size_t unit);

    virtual ~Texture();

};