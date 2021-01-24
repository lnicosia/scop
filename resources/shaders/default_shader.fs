#version 400 core

in vec3		FragPos;
in vec3		Normal;
in vec2		TexCoord;

out vec4	FragColor;

uniform sampler2D	texture1;
uniform sampler2D	texture2;

uniform vec3	camPos;
uniform vec3	lightPos;
uniform vec3	lightColor;
uniform vec3	objectColor;

void	main()
{
	float	ambientStrenght = 0.1;
	vec3	ambient = ambientStrenght * lightColor;
	vec3	norm = normalize(Normal);
	vec3	lightDir = normalize(lightPos - FragPos);
	float	diff = max(dot(norm, lightDir), 0.0);
	vec3	diffuse = diff * lightColor;

	float	specularStrength = 1;
	vec3	camDir = normalize(camPos - FragPos);
	vec3	reflectDir = reflect(-lightDir, norm);
	float	spec = pow(max(dot(camDir, reflectDir), 0.0), 32);
	vec3	specular = specularStrength * spec * lightColor;
	// Apply 20% mix between 2 textures
	//fragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.5);
	// One texture only
	//FragColor = texture(texture1, TexCoord);
	// All white
	vec3	result = (ambient + diffuse + specular) * objectColor;
	FragColor = vec4(result, 1.0);
}
