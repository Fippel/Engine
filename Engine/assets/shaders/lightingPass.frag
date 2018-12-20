#version 460 core

in vec3 vPos;
in vec3 vNormal;
in vec3 vColor;
in vec2 vUV;

out vec4 fragColor;

layout(location = 20) uniform sampler2D positions;
layout(location = 21) uniform sampler2D normals;
layout(location = 22) uniform sampler2D colors;
layout(location = 23) uniform sampler2D depth;

layout(location = 24) uniform sampler2D testTexture;

layout(location = 25) uniform sampler2D textInput;

void main() {
	vec3 pos = texture(positions, vUV).xyz;
	vec3 normal = texture(normals, vUV).xyz;
	vec4 color = texture(colors, vUV);
	//vec4 color = texture(diffuseTexture, vUV);

	//fragColor = vec4(normal, 1);
	
	vec4 ti = texture(textInput, vUV);
	if(ti.x == 1)
		fragColor = ti;
	else
		fragColor = color;

	// Texture test
	//vec4 color = texture(testTexture, vUV);
	//fragColor = color;
}