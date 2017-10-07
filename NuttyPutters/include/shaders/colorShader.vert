#version 440

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 in_colour;

layout (location = 0) out vec4 out_colour;

uniform mat4 transform;

void main()
{

	// Calculate screen position of vertex
	gl_Position = transform * vec4(position, 1.0);
	// Output colour to the fragment shader
	//out_colour = in_colour;
	out_colour = vec4(0.0, 1.0, 1.0, 1.0);
}