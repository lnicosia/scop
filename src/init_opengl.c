/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_opengl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 16:39:08 by lnicosia          #+#    #+#             */
/*   Updated: 2021/09/21 10:56:11 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmp_parser.h"
#include "scop.h"
#include <math.h>

int		init_textures(char *file, int flip, GLenum format, t_env *env)
{
	t_texture	texture;

	if (flip == 1)
	{
		if (parse_bmp_flipped(file, &texture))
		{
			texture.invalid = 1;
			return (custom_error("Failed to parse bmp\n"));
		}
	}
	else
	{
		if (parse_bmp(file, &texture))
		{
			ft_printf("Parsing not flipped\n");
			texture.invalid = 1;
			return (custom_error("Failed to parse bmp\n"));
		}
	}
	texture.name = file;
	glGenTextures(1, &env->textures[env->texture_count]);
	glBindTexture(GL_TEXTURE_2D, env->textures[env->texture_count]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.w, texture.h, 0, format,
	GL_UNSIGNED_BYTE, texture.pixels);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	ft_memdel((void**)&texture.pixels);
	env->texture_count++;
	ft_printf("Texture '%s' initialized\n", file);
	return (0);
}

void	error_callback(int error, const char *description)
{
	(void)error;
	ft_dprintf(STDERR_FILENO, "GLFW Error: %s\n", description);
}

void	init_camera(t_env *env)
{
	env->camera.vfov = 45.0f;
	env->camera.ratio = 1.0f;
	env->camera.t = 0.1f * tanf(to_radians(env->camera.vfov / 2.0f));
	env->camera.b = -env->camera.b;
	env->camera.r = env->camera.t * env->camera.ratio;
	env->camera.l = -env->camera.r;
	env->camera.n = 0.1f;
	env->camera.f = 100.0f;
	env->camera.pos = new_v3(0.0f, 0.0f, -3.0f);
	env->camera.front = new_v3(0.0f, 0.0, -1.0f);
	env->camera.up = new_v3(0.0f, 1.0f, 0.0f);
	env->camera.speed = 0.05f;
	env->camera.yaw = -90.0f;
	env->camera.pitch = 0.0f;
	env->sensi = 0.1f;
}

int		init_shader_textures_names(t_env *env)
{
	for (int i = 0; i < MAX_ACTIVE_TEXTURES; i++)
	{
		char	*nb;
		char	*material;
		if (!(nb = ft_itoa(i)))
			return (custom_error("Failed to itoa diffuse names\n"));
		if (!(material = ft_strjoin("material", nb)))
		{
			ft_strdel(&nb);
			return (custom_error("Failed to strjoin diffuse names\n"));
		}
		ft_strdel(&nb);
		if (!(env->diffuse_names[i] = ft_strjoin(material, ".diffuse")))
		{
			ft_strdel(&material);
			return (custom_error("Failed to strjoin diffuse names\n"));
		}
		ft_strdel(&material);
	}
	return (0);
}

int		init_opengl(t_env *env)
{
	glfwSetErrorCallback(error_callback);
	if (glfwInit() != GLFW_TRUE)
		ft_fatal_error("Failed to init GLFW\n", env);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	env->window = glfwCreateWindow(900, 900, "scop", NULL, NULL);
	if (!env->window)
		ft_fatal_error("Window could not be created", env);
	glfwMakeContextCurrent(env->window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		ft_fatal_error("Failed to init glad", env);
	glViewport(0, 0, 900, 900);
	glfwSetFramebufferSizeCallback(env->window, viewport_update_callback);
	glfwSetKeyCallback(env->window, key_callback);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	init_camera(env);
	init_textures("resources/objects/Square/brickwall.bmp", 0, GL_RGBA, env);
	init_textures("resources/textures/unicorn.bmp", 0, GL_RGBA, env);
	init_textures("resources/textures/awesomeface_alpha.bmp", 0, GL_RGBA, env);
	init_textures("resources/textures/container.bmp", 0, GL_RGB, env);
	init_textures("resources/textures/skybox1/right.bmp", 0, GL_RGB, env);
	init_textures("resources/objects/backpack/diffuse.bmp", 0, GL_RGB, env);
	init_textures("resources/objects/Spartan/textures/ODST_Shoulder_Mat_BaseColor.bmp", 0, GL_RGBA, env);
	init_textures("resources/objects/Spartan/textures/Spartan_Arms_Mat_BaseColor.bmp", 0, GL_RGBA, env);
	init_textures("resources/objects/Spartan/textures/Spartan_Chest_Mat_BaseColor.bmp", 0, GL_RGBA, env);
	init_textures("resources/objects/Spartan/textures/Spartan_Ears_Mat_BaseColor.bmp", 0, GL_RGBA, env);
	init_textures("resources/objects/Spartan/textures/Spartan_Helmet_Mat_BaseColor.bmp", 0, GL_RGBA, env);
	init_textures("resources/objects/Spartan/textures/Spartan_Legs_Mat_BaseColor.bmp", 0, GL_RGBA, env);
	init_textures("resources/objects/Spartan/textures/Spartan_Undersuit_Mat_BaseColor.bmp", 0, GL_RGBA, env);
	init_textures("resources/objects/swamp-location/source/terrain.bmp", 0, GL_RGBA, env);
	init_textures("resources/objects/swamp-location/source/grass.bmp", 0, GL_RGBA, env);
	init_textures("resources/objects/swamp-location/source/object.bmp", 0, GL_RGBA, env);
	init_textures("resources/objects/swamp-location/source/water.bmp", 0, GL_RGBA, env);
	init_textures("resources/objects/goreforged-greatsword/textures/lambert1_Base_Color.bmp", 0, GL_RGBA, env);
	char *skybox[] =
	{
		"resources/textures/skybox1/right.bmp",
		"resources/textures/skybox1/left.bmp",
		"resources/textures/skybox1/top.bmp",
		"resources/textures/skybox1/bottom.bmp",
		"resources/textures/skybox1/back.bmp",
		"resources/textures/skybox1/front.bmp"
	};
	int flipped[] =
	{
		1, 1, 0, 0, 1, 1
	};
	init_cubemap(skybox, flipped, GL_RGB, env);
	if (init_shader_textures_names(env))
		return (-1);
	reset_matrix(env->look_at_matrix);
	look_at(env->look_at_matrix, env->camera.pos,
		env->camera.front, env->camera.up);
	reset_matrix(env->projection_matrix);
	projection_matrix(&env->camera, env->projection_matrix);
	env->polygon_mode = GL_FILL;
	return (0);
}
