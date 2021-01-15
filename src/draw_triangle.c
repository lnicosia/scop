/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_triangle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 12:28:54 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/15 13:27:34 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include "scop.h"

int		init_triangle_shaders_program(t_env *env)
{
	unsigned int	vertex_shader;
	unsigned int	fragment_shader;
	float			vertices[] = { 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, -0.5f, -0.5f, 0.0f,
	0.0f, 0.0f, 1.0, 0.0f, 0.0f, -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	1.0f};
	unsigned int	indices[] = {0, 1, 3, 1, 2, 3};

	vertex_shader = init_pipeline_shader(GL_VERTEX_SHADER,
	"resources/shaders/default_shader.vs", env);
	fragment_shader = init_pipeline_shader(GL_FRAGMENT_SHADER,
	"resources/shaders/default_shader.fs", env);
	init_program(vertex_shader, fragment_shader, env);
	glGenVertexArrays(1, &env->vaos[0]);
	glGenBuffers(1, &env->vbos[0]);
	glGenBuffers(1, &env->ebos[0]);
	glBindVertexArray(env->vaos[0]);
	glBindBuffer(GL_ARRAY_BUFFER, env->vbos[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, env->ebos[0]);
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
	glUseProgram(env->shaders[0]);
	glUniform1i(glGetUniformLocation(env->shaders[0], "texture1"), 0);
	glUniform1i(glGetUniformLocation(env->shaders[0], "texture2"), 1);
	glUniformMatrix4fv(glGetUniformLocation(env->shaders[0], "transform"))
	return (0);
}

int		draw_triangle(t_env *env)
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, env->textures[0]);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, env->textures[1]);
	glBindVertexArray(env->vaos[0]);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	return (0);
}