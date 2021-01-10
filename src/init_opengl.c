/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_opengl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 16:39:08 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/10 16:42:39 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "scop.h"

void	error_callback(int error, const char *description)
{
	(void)error;
	ft_dprintf(STDERR_FILENO, "GLFW Error: %s\n", description);
}

int		init_opengl(t_env *env)
{
	glfwSetErrorCallback(error_callback);
	if (glfwInit() != GLFW_TRUE)
	{
		ft_fatal_error("Failed to init GLFW", env);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	env->window = glfwCreateWindow(1600, 900, "scop", NULL, NULL);
	if (!env->window)
	{
		ft_fatal_error("Window could not be created", env);
	}
	glfwMakeContextCurrent(env->window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		ft_fatal_error("Failed to init glad", env);
	}
	glViewport(0, 0, 1600, 900);
	glfwSetFramebufferSizeCallback(env->window, viewport_update_callback);
	return (0);
}
