#version 330 core

attribute vec3 position;        // Position of the vertex
attribute vec2 texCoord;        // UV texture coordinates
attribute vec3 normal;          // Normal vector to the vertex

varying vec2 texCoord0;         // To interpolate UV values
varying vec3 position0;         // To interpolate position values
varying vec3 normal0;           // To interpolate normal values

uniform mat4 perspective;       // Camera perspective matrix
uniform mat4 model;             // Transformation matrix
uniform mat4 view;              // Camera view matrix

void main() {
    // Evaluate model view matrix
    mat4 model_view = view * model;
    // Evaluate vertex projection
    vec4 temp = model_view * vec4(position, 1.0);
    gl_Position = perspective * temp;
    // Copy values to interpolate
    position0 = temp.xyz;
    normal0 = transpose(inverse(mat3(model_view))) * normal;
    texCoord0 = texCoord;
}