#version 400 core

struct		Material
{
	vec3		ambient;
	sampler2D	diffuse;
	vec3		specular;
	float		shininess;
};

struct		Light
{
	vec3	pos;
	vec3	ambient;
	vec3	diffuse;
	vec3	specular;
};

in vec3		FragPos;
in vec3		Normal;
in vec2		TexCoord;

out vec4	FragColor;

uniform sampler2D	texture1;
uniform sampler2D	texture2;

uniform Material material0;
uniform Light	 light;

uniform vec3	camPos;

void	main()
{
	FragColor = vec4(texture(material0.diffuse, TexCoord));
}
