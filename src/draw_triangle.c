/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_triangle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 12:28:54 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/17 19:43:27 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include "scop.h"
#include <math.h>

int		init_triangle_shaders_program(t_env *env)
{
	unsigned int	vertex_shader;
	unsigned int	fragment_shader;
	unsigned int	indices[] = {0, 1, 3, 1, 2, 3};

	init_object("", "plane", env);
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
	glBufferData(GL_ARRAY_BUFFER, env->objects[0].size,
	env->objects[0].vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, env->ebos[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
	GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
	(void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
	(void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glUseProgram(env->shaders[0]);
	glUniform1i(glGetUniformLocation(env->shaders[0], "texture1"), 0);
	glUniform1i(glGetUniformLocation(env->shaders[0], "texture2"), 1);
	//glUniformMatrix4fv(glGetUniformLocation(env->shaders[0], "transform"),
	//1, GL_TRUE, env->mat);
	return (0);
}

void	rotate_z_cpu(float *vertices, float rotation)
{
	float	tmp;
	/*t_v3	center;

	center.x = (vertices[0] + vertices[5] + vertices[10] + vertices[15]) / 4.0f;
	center.y = (vertices[1] + vertices[6] + vertices[11] + vertices[16]) / 4.0f;

	vertices[0] = (vertices[0] - center.x) / 2.0f;
	vertices[1] = (vertices[1] - center.y) / 2.0f;*/
	tmp = vertices[0];
	vertices[0] = cosf(rotation) * vertices[0] - sinf(rotation) * vertices[1];
	vertices[1] = sinf(rotation) * tmp + cosf(rotation) * vertices[1];
	/*vertices[0] = (vertices[0] + center.x) / 2.0f;
	vertices[1] = (vertices[1] + center.y) / 2.0f;

	vertices[5] = (vertices[5] - center.x) / 2.0f;
	vertices[6] = (vertices[6] - center.y) / 2.0f;*/
	tmp = vertices[5];
	vertices[5] = cosf(rotation) * vertices[5] - sinf(rotation) * vertices[6];
	vertices[6] = sinf(rotation) * tmp + cosf(rotation) * vertices[6];
	/*vertices[5] = (vertices[5] + center.x) / 2.0f;
	vertices[6] = (vertices[6] + center.y) / 2.0f;

	vertices[10] = (vertices[10] - center.x) / 2.0f;
	vertices[11] = (vertices[11] - center.y) / 2.0f;*/
	/*tmp = vertices[10];
	vertices[10] = cosf(rotation) * vertices[10] - sinf(rotation) * vertices[11];
	vertices[11] = sinf(rotation) * tmp + cosf(rotation) * vertices[11];*/
	/*vertices[10] = (vertices[10] + center.x) / 2.0f;
	vertices[11] = (vertices[11] + center.y) / 2.0f;

	vertices[15] = (vertices[15] - center.x) / 2.0f;
	vertices[16] = (vertices[16] - center.y) / 2.0f;*/
	tmp = vertices[15];
	vertices[15] = cosf(rotation) * vertices[15] - sinf(rotation) * vertices[16];
	vertices[16] = sinf(rotation) * tmp + cosf(rotation) * vertices[16];
	/*vertices[15] = (vertices[15] + center.x) / 2.0f;
	vertices[16] = (vertices[16] + center.y) / 2.0f;*/
}

int		draw_triangle(t_env *env)
{
	//move_object(&env->objects[0].instances[0], new_v3(0.0f, 0.0f, 0.01f));
	//rotate_object(&env->objects[0].instances[0], new_v3(0.0f, 0.0f, 0.01f));
	rotate_object(&env->objects[0].instances[0], new_v3(0.0f, 0.0f, 0.01f));
	//scale_object(&env->objects[0].instances[0], new_v3(0.0f, 0.0f, 0.1f));
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, env->textures[0]);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, env->textures[1]);
	glBindVertexArray(env->vaos[0]);
	draw_object(&env->objects[0], env);
	return (0);
}