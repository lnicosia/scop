/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_triangle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 12:28:54 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/12 21:20:48 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include "shader.h"

int		init_vertex_shader(t_env *env)
{
	unsigned int	vertex_shader;
	const char		*vertex_shader_source;

	vertex_shader_source = read_shader("resources/shaders/default_shader.vs");
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
	glCompileShader(vertex_shader);
	env->success = GLFW_TRUE;
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &env->success);
	ft_memdel((void**)&vertex_shader_source);
	if (env->success != GLFW_TRUE)
	{
		glGetShaderInfoLog(vertex_shader, 512, NULL, env->log);
		custom_error("{yellow}Failed to compile vertex shader\n");
		return (custom_error(env->log));
	}
	return (vertex_shader);
}

int		init_fragment_shader(t_env *env)
{
	unsigned int	fragment_shader;
	const char		*fragment_shader_source;

	fragment_shader_source = read_shader("resources/shaders/default_shader.fs");
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
	glCompileShader(fragment_shader);
	env->success = GLFW_TRUE;
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &env->success);
	ft_memdel((void**)&fragment_shader_source);
	if (env->success != GLFW_TRUE)
	{
		glGetShaderInfoLog(fragment_shader, 512, NULL, env->log);
		custom_error("{yellow}Failed to compile fragment shader\n");
		return (custom_error(env->log));
	}
	return (fragment_shader);
}

int		init_program(unsigned int vertex_shader, unsigned int fragment_shader,
t_env *env)
{
	if ((env->tuto_shader = glCreateProgram()) == 0)
		return (custom_error("Failed to create shader program\n"));
	glAttachShader(env->tuto_shader, vertex_shader);
	glAttachShader(env->tuto_shader, fragment_shader);
	glLinkProgram(env->tuto_shader);
	env->success = GL_FALSE;
	glGetProgramiv(env->tuto_shader, GL_LINK_STATUS, &env->success);
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
	if (env->success != GL_TRUE)
	{
		glGetProgramInfoLog(env->tuto_shader, 512, NULL, env->log);
		custom_error("Failed to compile shader program\n");
		return (custom_error(env->log));
	}
	return (0);
}

int		init_triangle_shaders_program(t_env *env)
{
	unsigned int	vertex_shader;
	unsigned int	fragment_shader;
	float			vertices[] = { 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, -0.5f, -0.5f, 0.0f,
	0.0f, 0.0f, 1.0, 0.0f, 0.0f, -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	1.0f};
	unsigned int	indices[] = {0, 1, 3, 1, 2, 3};

	/*vertex_shader = init_vertex_shader(env);
	fragment_shader = init_fragment_shader(env);*/
	vertex_shader = init_pipeline_shader(GL_VERTEX_SHADER,
	"resources/shaders/default_shader.vs", env);
	fragment_shader = init_pipeline_shader(GL_FRAGMENT_SHADER,
	"resources/shaders/default_shader.fs", env);
	init_program(vertex_shader, fragment_shader, env);
	glGenVertexArrays(1, &env->tuto_vao);
	glGenBuffers(1, &env->tuto_vbo);
	glGenBuffers(1, &env->tuto_ebo);
	glBindVertexArray(env->tuto_vao);
	glBindBuffer(GL_ARRAY_BUFFER, env->tuto_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, env->tuto_ebo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
	GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
	(void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
	(void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
	(void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);
	return (0);
}

int		draw_triangle(t_env *env)
{
	glUseProgram(env->tuto_shader);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBindVertexArray(env->tuto_vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, env->tuto_ebo);
	glBindTexture(GL_TEXTURE_2D, env->tuto_texture);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	return (0);
}
