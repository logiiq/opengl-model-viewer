#version 400 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexturePos;

// # To fragment shader # //
out vec3 normPos;
out vec2 texPos;
out vec3 fragPos;

uniform mat4 finalMat;
uniform mat4 model;
uniform mat4 view;
uniform mat3 normal_mtx;

void main()
{
    gl_Position = finalMat * vec4(aPos, 1.0f);
    fragPos = vec3(view * model * vec4(aPos, 1.0f)); // transform fragment to viewspace
    //normPos = normal_mtx * aNormal; // must implement in this version
    normPos = mat3(transpose(inverse(view * model))) * aNormal; // debug
    texPos = aTexturePos;
}