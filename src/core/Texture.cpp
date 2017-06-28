#include "Texture.hpp"
#include "Utils.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture(const std::string& filename) {
    int width, height, numComponents;
    // Read image data
    unsigned char* imagedata = stbi_load(filename.c_str(), &width, &height, &numComponents, 4);
    if (imagedata == NULL) die("Failed to load texture " + filename);
    // Generate texture buffer
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imagedata);
    stbi_image_free(imagedata);
}

void Texture::bind(size_t unit) {
    // Check unit to be possible
    if(!(unit >= 0 && unit <= 31)) die("Texture: unit out of range");
    // Activate unit and bind texture
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, texture);
}

Texture::~Texture() {
    // Clear texture buffer
    glDeleteTextures(1, &texture);
}