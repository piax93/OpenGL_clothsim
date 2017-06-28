#include "Shader.hpp"
#include "Globals.hpp"
#include "Utils.hpp"
#include "Transformation.hpp"
#include <glm/gtc/type_ptr.hpp>


Shader::Shader(const std::string& name) {
    // Create shader program
    program = glCreateProgram();
    // Load vertex and fragment shaders
    vertexShader = loadShader(SHADER_FOLDER + name + VERTEX_SHADER_EXT, GL_VERTEX_SHADER);
    fragmentShader = loadShader(SHADER_FOLDER + name + FRAGMENT_SHADER_EXT, GL_FRAGMENT_SHADER);
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    // Bind attribute variables
    glBindAttribLocation(program, POSITION_ATTRIBUTE, "position");
    glBindAttribLocation(program, TEXTURE_UV_ATTRIBUTE, "texCoord");
    glBindAttribLocation(program, NORMAL_ATTRIBUTE, "normal");
    // Link and validate program
    glLinkProgram(program);
    checkShaderError(program, GL_LINK_STATUS, true, "Shader program failed to link, ");
    glValidateProgram(program);
    checkShaderError(program, GL_VALIDATE_STATUS, true, "Shader program failed to validate, ");
    // Bind uniform variables
    uniforms[MODEL_U] = glGetUniformLocation(program, "model");
    uniforms[PERSPECTIVE_U] = glGetUniformLocation(program, "perspective");
    uniforms[VIEW_U] = glGetUniformLocation(program, "view");
    uniforms[LIGHT_POS_U] = glGetUniformLocation(program, "light_pos");
    uniforms[LIGHT_INTENSITY_U] = glGetUniformLocation(program, "light_intensity");
    for (size_t i = 0; i < NUM_UNIFORMS; i++)
        if (uniforms[i] == -1) die("Wrong uniform binding");
}

void Shader::bind() {
    // Bind shader program
    glUseProgram(program);
}

void Shader::update(const Camera& cam, const OmniLight& light) {
    // Retrieve and update uniform variables
    glm::mat4 persp(cam.getPerspective());
    glm::mat4 model_view(cam.getView());
    glm::vec3 light_model(model_view * glm::vec4(light.position, 1.0f));
    glUniformMatrix4fv(uniforms[PERSPECTIVE_U], 1, GL_FALSE, glm::value_ptr(cam.getPerspective()));
    glUniformMatrix4fv(uniforms[VIEW_U], 1, GL_FALSE, glm::value_ptr(cam.getView()));
    glUniform3fv(uniforms[LIGHT_POS_U], 1, glm::value_ptr(light_model));
    glUniform1fv(uniforms[LIGHT_INTENSITY_U], 1, &light.intensity);
    transform();
}

void Shader::transform() {
    glUniformMatrix4fv(uniforms[MODEL_U], 1, GL_FALSE, glm::value_ptr(Transformation::getMatrix()));
}

GLuint Shader::loadShader(const std::string& filename, GLenum type) {
    // Create shader handle
    GLuint shader = glCreateShader(type);
    if (shader == 0) die("Shader creation failed");
    // Read source from file
    std::string shaderSource = readFileToString(filename);
    // Compile shader
    const GLchar* shaderSourceChar[1] = { shaderSource.c_str() };
    GLint shaderSourceLen[1] = { (GLint) shaderSource.length() };
    glShaderSource(shader, 1, shaderSourceChar, shaderSourceLen);
    glCompileShader(shader);
    checkShaderError(shader, GL_COMPILE_STATUS, false, "Error compiling shader, ");
    return shader;
}

void Shader::checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage) {
    GLint success = 0;
    GLchar error[1024] = { 0 };
    if (isProgram) glGetProgramiv(shader, flag, &success);
    else glGetShaderiv(shader, flag, &success);
    if (success == GL_FALSE) {
        if (isProgram) glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        else glGetShaderInfoLog(shader, sizeof(error), NULL, error);
        die(errorMessage + error);
    }
}

Shader::~Shader() {
    // Clear all
    glDetachShader(program, vertexShader);
    glDetachShader(program, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteProgram(program);
}