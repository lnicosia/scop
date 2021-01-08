/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_opengl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 17:56:35 by lnicosia          #+#    #+#             */
/*   Updated: 2020/02/24 18:25:22 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "libft.h"

int	init_opengl()
{
	//ft_printf("OpenGL vendor: %s\n", glGetString(GL_VENDOR));
	if (glfwInit() == GLFW_TRUE)
	{
	}
	else
	{
	}
	return (0);
}
