#version 330 core

out vec4 FragColor;

in vec3 gouraud;

void main() {
    FragColor = vec4(gouraud, 1.0f);
}