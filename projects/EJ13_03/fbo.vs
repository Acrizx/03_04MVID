#version 330 core

layout (location=0) in vec3 aPos;
layout (location=1) in vec2 aUv;
layout (location=2) in vec3 aNormal;

out vec2 uv;
out vec2 blurTextureCoords[11];

uniform float targetWidth;

void main() {
    uv = aUv;
    gl_Position = vec4(vec2(aPos), 0.0, 1.0);
}