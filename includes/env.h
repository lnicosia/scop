/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 14:57:26 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/16 15:11:39 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H
# include "glad/glad.h"
# include "object.h"
# include "camera.h"
# include <GLFW/glfw3.h>
# define MAX_VAO 1
# define MAX_VBO 1
# define MAX_EBO 1
# define MAX_TEXTURES 2
# define MAX_SHADERS 2
# define MAX_OBJECTS 1

/*
** Defines all the env structure that will contains everything globally needed
** by the program
*/

typedef struct		s_env
{
	t_camera		camera;
	uint32_t		**images;
	GLFWwindow		*window;
	t_object		objects[MAX_OBJECTS];
	size_t			shader_count;
	size_t			vao_count;
	size_t			vbo_count;
	size_t			ebo_count;
	size_t			texture_count;
	size_t			object_count;
	unsigned int	shaders[MAX_SHADERS];
	unsigned int	vaos[MAX_VAO];
	unsigned int	vbos[MAX_VBO];
	unsigned int	ebos[MAX_EBO];
	unsigned int	textures[MAX_TEXTURES];
	float			matrix[16];
	int				direction;
	char			log[512];
	int				success;
	char			padding[4];
}					t_env;

#endif
