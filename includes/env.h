/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 14:57:26 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/21 18:54:54 by lnicosia         ###   ########.fr       */
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
	GLFWwindow		*window;
	t_object		objects[MAX_OBJECTS];
	double			mouse_x_start;
	double			mouse_y_start;
	size_t			shader_count;
	size_t			vao_count;
	size_t			vbo_count;
	size_t			ebo_count;
	size_t			texture_count;
	size_t			object_count;
	unsigned int	shaders[MAX_SHADERS];
	unsigned int	textures[MAX_TEXTURES];
	t_camera		camera;
	unsigned int	polygon_mode;
	float			matrix[16];
	float			projection_matrix[16];
	int				direction;
	char			log[512];
	int				success;
}					t_env;

#endif
