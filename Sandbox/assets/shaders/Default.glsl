// Flat Color Shader

#type vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out DATA
{
    vec4 color;
} vs_out;

void main()
{
	gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
    vs_out.color = a_Color;
}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

in DATA
{
    vec4 color;
} fs_in;

void main()
{
	color = fs_in.color;
}
