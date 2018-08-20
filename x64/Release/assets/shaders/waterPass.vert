#version 460 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 uv;

out vec3 vPos;
out vec3 vNormal;
out vec3 vColor;
out vec2 vUV;

layout(location = 0) uniform mat4 m;
layout(location = 1) uniform mat4 v;
layout(location = 2) uniform mat4 p;

void main() {
	gl_Position = p * v * m * vec4(pos.x, 0.0, pos.y, 1.0);
	vUV = vec2(pos.x/2.0 + 0.5, pos.y/2.0 + 0.5);
}