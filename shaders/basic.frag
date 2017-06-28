#version 330 core

varying vec2 texCoord0;         // Interpolated UV texture coordinate
varying vec3 position0;         // Interpolated vertex position
varying vec3 normal0;           // Interpolatex vertex normal

uniform sampler2D diffuse;      // Texture
uniform vec3 light_pos;         // Position of omni light in 3D space
uniform float light_intensity;  // Intensity of omni light

void main() {
    // Evaluate light ray
    vec3 r = (position0 - light_pos);
    // Evaluate direct illumination
	float direct = light_intensity * max(-dot(normalize(r), normal0), 0.0) / (4 * 3.14 * dot(r, r));
    // Evalute fragment color
	gl_FragColor = texture2D(diffuse, texCoord0) * (direct + 0.1);
}