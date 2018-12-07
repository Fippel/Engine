#version 460 core

in vec2 TexCoords;
out vec4 color;

layout (location = 20) uniform sampler2D text;
//layout (location = 21) uniform sampler2D lightInput;
out vec4 fragColor;
//uniform vec3 textColor;

void main()
{    
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
    color = vec4(vec3(1, 1, 1), 1.0) * sampled;
	//color = texture(inputasd, TexCoords);
	//color = vec4(1, 0, 0, 0);
	//vec4 li = texture(lightInput, TexCoords);
	fragColor = color;
}  