#version 330 core

in vec2 UV;
out vec4 FragColor;

uniform sampler2D tex_1;

void main() {
    FragColor = texture(tex_1, vec2(UV.x*4 ,UV.y*4));
}