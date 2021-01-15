#version 330
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTextCoord;

out vec2	TextCoord;

uniform mat4	model;
uniform mat4	view;
uniform mat4	projection;

void	main()
{
	gl_Position = model * vec4(aPos, 1.0);
	TextCoord = aTextCoord;
}
