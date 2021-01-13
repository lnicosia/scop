/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 14:57:26 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/13 22:14:47 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H
# include "glad/glad.h"
# include "object.h"
# include <GLFW/glfw3.h>
# define MAX_VAO 3
# define MAX_VBO 1
# define MAX_EBO 1

/*
** Defines all the env structure that will contains everything globally needed
** by the program
*/

typedef struct		s_env
{
	uint32_t		**images;
	GLFWwindow		*window;
	t_object		*objects;
	unsigned int	*shaders;
	unsigned int	vaos[MAX_VAO];
	unsigned int	vbos[MAX_VBO];
	unsigned int	ebos[MAX_EBO];
	unsigned int	tuto_shader;
	unsigned int	tuto_vao;
	unsigned int	tuto_vbo;
	unsigned int	tuto_ebo;
	unsigned int	tuto_texture;
	char			log[512];
	int				success;
	char			padding[4];
}					t_env;

#endif
