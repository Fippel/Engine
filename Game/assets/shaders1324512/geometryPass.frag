#version 460 core

in vec3 vPos;
in vec3 vNormal;
in vec3 vColor;
in vec2 vUV;

layout(location = 0) out vec3 gPosition;
layout(location = 1) out vec3 gNormal;
layout(location = 2) out vec4 gColor;

layout(location = 25) uniform sampler2D diffuseTexture;

void main() {
	gPosition = vPos;
	gNormal = vNormal;
	vec4 c = texture(diffuseTexture, vUV);
	gColor = c;
	//gColor = vec4(vColor, 1);
}