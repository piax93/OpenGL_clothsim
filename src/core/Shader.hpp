#pragma once

#include <string>
#include <GL/glew.h>
#include "Camera.hpp"

#define SHADER_FOLDER "shaders/"            // Folder containing shaders
#define VERTEX_SHADER_EXT ".vert"           // File extension for vertex shader
#define FRAGMENT_SHADER_EXT ".frag"         // File extension for fragment shader

/**
 * Struct representing a white onmilight
 */
struct OmniLight {
    glm::vec3 position;     // Position in 3D space
    float intensity;        // Light intensity
    OmniLight(const glm::vec3& _pos, float _intensity) : position(_pos), intensity(_intensity) {}
};


/**
 * Shader loading class
 */
class Shader {

private:
    /**
     * Enumeration to keep track of uniform variables
     */
    enum {
        PERSPECTIVE_U, VIEW_U, MODEL_U, LIGHT_POS_U, LIGHT_INTENSITY_U, NUM_UNIFORMS
    };
    
    GLuint program;                     // Handle to shader program
    GLuint vertexShader;                // Handle to vertex shader
    GLuint fragmentShader;              // Handle to fragment shader
    GLuint uniforms[NUM_UNIFORMS];      // Handles to uniform variables

    /**
     * Load shader from file
     * @param filename Path to shader file
     * @param type OpenGL shader type
     * @return OpenGL handle to shader
     */
    static GLuint loadShader(const std::string& filename, GLenum type);
    
    /**
     * Check and print shader error (it terminates the execution in case of error)
     * @param shader Handle to shader
     * @param flag Flat to point out which error to check for
     * @param isProgram True if the passed handle is a shader program, false otherwise
     * @param errorMessage Error message to prepend
     */
    static void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);

public:

    /**
     * Shader constructor
     * @param name Name of the shader to load
     */
    Shader(const std::string& name);

    /**
     * Update shader variables
     * @param cam Scene camera
     * @param light Scene omnilight
     */
    void update(const Camera& cam, const OmniLight& light);

    /**
     * Update model matrix
     */
    void transform();
    
    /**
     * Bind shader 
     */
    void bind();

    virtual ~Shader();

};