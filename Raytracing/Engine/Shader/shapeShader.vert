#version 410 core

layout(location = 0) in vec2 a_position;

out vec4 v_color;

uniform vec4 u_color;

void main()
{
	gl_Position = vec4(a_position, 1.0f, 1.0f);
	v_color = u_color;
}