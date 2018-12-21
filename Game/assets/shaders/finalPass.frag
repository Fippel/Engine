#version 460 core

in vec3 vPos;
in vec2 vUV;

out vec4 fragColor;

layout(location = 20) uniform sampler2D lightInput;
layout(location = 21) uniform sampler2D textInput;

void main() {

	vec4 color = texture(lightInput, vUV);
	vec4 ti = texture(textInput, vUV);
	if(ti.x == 1)
		fragColor = ti;
	else
		fragColor = color;
}