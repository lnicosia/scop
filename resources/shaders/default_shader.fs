#version 330 core

in vec2		TexCoord;

out vec4	fragColor;

uniform sampler2D	texture1;
uniform sampler2D	texture2;

void	main()
{
	// Apply 20% mix between 2 textures
	//fragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.5);
	// One texture only
	fragColor = texture(texture1, TexCoord);
	// All white
	//fragColor = vec4(1, 1, 1, 1);
}
