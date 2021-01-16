/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_opengl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 16:39:08 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/16 15:18:29 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "scop.h"

int		init_textures(char *file, GLenum format, t_env *env)
{
	unsigned char	*data;

	if (parse_bmp(file, &data))
		return (custom_error("Failed to parse bmp\n"));
	glGenTextures(1, &env->textures[env->texture_count]);
	glBindTexture(GL_TEXTURE_2D, env->textures[env->texture_count]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 512, 512, 0, format,
	GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	ft_memdel((void**)&data);
	env->texture_count++;
	return (0);
}

void	error_callback(int error, const char *description)
{
	(void)error;
	ft_dprintf(STDERR_FILENO, "GLFW Error: %s\n", description);
}

void	init_camera(t_env *env)
{
	env->camera.l = 1.0f;
	env->camera.r = 1.0f;
	env->camera.b = 1.0f;
	env->camera.t = 1.0f;
	env->camera.n = 0.1;
	env->camera.f = 100.0f;
	env->camera.pos = new_v3(0, 0, -3);
}

int		init_opengl(t_env *env)
{
	glfwSetErrorCallback(error_callback);
	if (glfwInit() != GLFW_TRUE)
		ft_fatal_error("Failed to init GLFW", env);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	env->window = glfwCreateWindow(1600, 900, "scop", NULL, NULL);
	if (!env->window)
		ft_fatal_error("Window could not be created", env);
	glfwMakeContextCurrent(env->window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		ft_fatal_error("Failed to init glad", env);
	glViewport(0, 0, 1600, 900);
	glfwSetFramebufferSizeCallback(env->window, viewport_update_callback);
	glfwSetInputMode(env->window, GLFW_STICKY_KEYS, GLFW_TRUE);
	glfwSetKeyCallback(env->window, key_callback);
	init_camera(env);
	init_textures("resources/textures/container.bmp", GL_RGB, env);
	init_textures("resources/textures/awesomeface_alpha.bmp", GL_RGBA, env);
	reset_matrix(env->matrix);
	init_triangle_shaders_program(env);
	add_object(0, env);
	scale_object(&env->objects[0].instances[0], new_v3(-0.75, -0.5, 0));
	//rotate_object(&env->objects[0].instances[0], new_v3(0, 0, 0.5));
	//add_object(0, env);
	return (0);
}
