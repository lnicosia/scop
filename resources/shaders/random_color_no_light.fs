#version 400 core

out vec4 FragColor;
uniform float nb_vertices;


void	main()
{
	vec3 color = vec3((gl_PrimitiveID / nb_vertices) * 0.5 + 0.25);
	FragColor = vec4(color, 1.0);
}