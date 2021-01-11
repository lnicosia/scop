/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 14:57:26 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/11 21:42:06 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H
# include "glad/glad.h"
# include "shader.h"
# include "object.h"
# include <GLFW/glfw3.h>

/*
** Defines all the env structure that will contains everything globally needed
** by the program
*/

typedef struct		s_env
{
	GLFWwindow		*window;
	t_object		*objects;
	unsigned int	*shaders;
	unsigned int	*vaos;
	unsigned int	*vbos;
	unsigned int	tuto_shader;
	unsigned int	tuto_vao;
	unsigned int	tuto_vbo;
	int				success;
	char			log[512];
}					t_env;

#endif
