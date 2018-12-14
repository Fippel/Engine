#version 460 core

in vec2 vUV;

layout(location = 0) out vec4 gColor;

layout(location = 25) uniform sampler2D diffuseTexture;

void main() {
	gColor = vec4(0.0, 0.0, 1.0, 1.0);
}