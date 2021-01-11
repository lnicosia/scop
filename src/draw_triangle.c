/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_triangle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 12:28:54 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/11 21:45:17 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"

int		init_vertex_shader(t_env *env)
{
	unsigned int	vertex_shader;
	const char		*vertex_shader_source;

	vertex_shader_source = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0";
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	if (vertex_shader == 0)
		return (custom_error("Failed to init vertex shader\n"));
	glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
	glCompileShader(vertex_shader);
	env->success = GLFW_TRUE;
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &env->success);
	if (env->success != GLFW_TRUE)
	{
		glGetShaderInfoLog(vertex_shader, 512, NULL, env->log);
		custom_error("Failed to compile vertex shader\n");
		return (custom_error(env->log));
	}
	return (vertex_shader);
}

int		init_fragment_shader(t_env *env)
{
	unsigned int	fragment_shader;
	const char		*fragment_shader_source;

	fragment_shader_source = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\0";
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
	glCompileShader(fragment_shader);
	env->success = GLFW_TRUE;
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &env->success);
	if (env->success != GLFW_TRUE)
	{
		glGetShaderInfoLog(fragment_shader, 512, NULL, env->log);
		custom_error("Failed to compile fragment shader\n");
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
	const float		vertices[] = { -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f,
	0.0f, 0.5f, 0.0f };

	vertex_shader = init_vertex_shader(env);
	fragment_shader = init_fragment_shader(env);
	init_program(vertex_shader, fragment_shader, env);
	glGenVertexArrays(1, &env->tuto_vao);
	glGenBuffers(1, &env->tuto_vbo);
	glBindVertexArray(env->tuto_vao);
	glBindBuffer(GL_ARRAY_BUFFER, env->tuto_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
	(void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	return (0);
}

int		draw_triangle(t_env *env)
{
	glUseProgram(env->tuto_shader);
	glBindVertexArray(env->tuto_vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	return (0);
}
