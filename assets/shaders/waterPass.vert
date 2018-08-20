#version 460 core

in vec2 position;

out vec2 textureCoords;

layout(location = 0) uniform mat4 m;
layout(location = 1) uniform mat4 v;
layout(location = 2) uniform mat4 p;

void main() {
	gl_Position = p * v * m * vec4(position.x, 0.0, position.y, 1.0);
	textureCoords = vec2(position.x/2.0 + 0.5, position.y/2.0 + 0.5);
}