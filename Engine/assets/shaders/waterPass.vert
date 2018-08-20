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
	vPos = vec3(m * vec4(pos, 1)).xyz;
	vUV = vec2(vPos.x/2.0 + 0.5, vPos.y/2.0 + 0.5);
	gl_Position = p * v * m * vec4(vPos, 1);
}