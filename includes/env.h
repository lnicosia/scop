/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 14:57:26 by lnicosia          #+#    #+#             */
/*   Updated: 2021/09/16 09:28:37 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H
# include "glad/glad.h"
# include "object.h"
# include "camera.h"
# include "cubemap.h"
# include <GLFW/glfw3.h>
# define MAX_VAO 1
# define MAX_VBO 1
# define MAX_EBO 1
# define MAX_TEXTURES 20
# define USABLE_TEXTURES 5
# define MAX_SHADERS 4
# define MAX_OBJECTS 2
# define MAX_LIGHTS 1
# define MAX_CUBEMAPS 1

enum	e_light_mode
{
	LIGHT_ON,
	LIGHT_OFF,
};

enum	e_texture_mode
{
	SINGLE_TEXTURE,
	MULTIPLE_TEXTURES,
};

enum	e_yes_no
{
	YES,
	NO
};

/*
** Defines all the env structure that will contains everything globally needed
** by the program
*/

typedef struct		s_env
{
	GLFWwindow		*window;
	t_object		objects[MAX_OBJECTS];
	t_object		lights[MAX_LIGHTS];
	t_cubemap		cubemaps[MAX_CUBEMAPS];
	double			mouse_x_start;
	double			mouse_y_start;
	size_t			shader_count;
	size_t			vao_count;
	size_t			vbo_count;
	size_t			ebo_count;
	size_t			texture_count;
	size_t			object_count;
	size_t			cubemap_count;
	size_t			selected_object;
	const char		*diffuse_names[MAX_ACTIVE_TEXTURES];
	unsigned int	shaders[MAX_SHADERS];
	unsigned int	textures[MAX_TEXTURES];
	t_camera		camera;
	unsigned int	polygon_mode;
	unsigned int	current_text;
	unsigned int	texture_mode;
	float			look_at_matrix[16];
	float			projection_matrix[16];
	float			last_frame;
	float			sensi;
	int				direction;
	char			log[512];
	unsigned int	instance_count;
	int				success;
	int				light_mode;
	int				draw_skybox;
	int				selected_axe;
	//char			padding[4];
}					t_env;

#endif
