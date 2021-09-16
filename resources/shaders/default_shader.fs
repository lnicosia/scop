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
	vec4 textColor = texture(material0.diffuse, TexCoord);

	// Ambient
	float	ambientStrenght = 0.1;
	vec3	ambient = vec3(textColor) * light.ambient;

	// Diffuse
	vec3	norm = normalize(Normal);
	vec3	lightDir = normalize(light.pos - FragPos);
	float	diff = max(dot(norm, lightDir), 0.0);
	vec3	diffuse = diff * vec3(textColor) * light.diffuse;

	// Specular
	vec3	camDir = normalize(camPos - FragPos);
	vec3	reflectDir = reflect(-lightDir, norm);
	float	spec = pow(max(dot(camDir, reflectDir), 0.0), material0.shininess);
	vec3	specular = (spec * material0.specular) * light.specular;

	vec3	result = (ambient + diffuse + specular);

	// Light
	FragColor = vec4(result, textColor.a);
}
