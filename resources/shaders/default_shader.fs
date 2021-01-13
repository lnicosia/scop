#version 330 core

in vec3		ourColor;
in vec2		TextCoord;

out vec4	fragColor;

uniform sampler2D	texture1;
uniform sampler2D	texture2;

void	main()
{
	fragColor = mix(texture(texture1, TextCoord), texture(texture1, TextCoord), 0.2);
}
