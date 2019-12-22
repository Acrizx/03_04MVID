#version 330 core

in vec2 UV;
out vec4 FragColor;

uniform sampler2D tex_1;

void main() {
	vec2 flipTexture= vec2(UV.x,-UV.y);
    FragColor = texture(tex_1, flipTexture);
}