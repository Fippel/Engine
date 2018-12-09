#version 460 core

layout (location = 0) in vec3 pos; // <vec2 pos, vec2 tex>
layout (location = 3) in vec2 uv;
out vec2 TexCoords;

layout (location = 33) uniform mat4 projection;

void main()
{
    gl_Position = projection * vec4(pos.xy, 0.0, 1.0);
	//gl_Position = vec4(pos, 1.0);
    TexCoords = uv;
}  