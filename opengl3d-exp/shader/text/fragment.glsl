#version 400 core
out vec4 FragColor;
in vec2 texCoords;

uniform sampler2D sampler;
uniform vec4 color;

void main() {
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(sampler, texCoords).r);
    FragColor = sampled * color;
}