#version 400 core

in vec3 TextCoords;
uniform samplerCube cubemap;

out	vec4	FragColor;

void	main()
{
	FragColor = texture(cubemap, TextCoords);
}