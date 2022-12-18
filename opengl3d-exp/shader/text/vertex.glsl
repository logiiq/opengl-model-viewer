#version 400 core
layout (location = 0) in vec4 aCoords;

uniform mat4 pvm;

out vec2 texCoords;

void main() {
    gl_Position = pvm * vec4(aCoords.xy, 0.0f, 1.0f);
    texCoords = aCoords.zw;
}