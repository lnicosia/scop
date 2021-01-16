/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_triangle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 12:28:54 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/16 12:16:16 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include "scop.h"

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

int		draw_triangle(t_env *env)
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, env->textures[0]);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, env->textures[1]);
	/*if (env->mat[3] < -0.5)
		env->direction = 1;
	if (env->mat[3] > 0.5)
		env->direction = 0;
	if (env->direction == 1)
	{
		env->mat[3] += 0.005;
		//env->m./at[13] += 0.005;
	}
	else
	{
		env->mat[3] -= 0.005;
		//env->mat[13] -= 0.005;
	}*/
	/*glUseProgram(env->shaders[0]);
	glUniformMatrix4fv(glGetUniformLocation(env->shaders[0], "model"),
	1, GL_TRUE, env->mat);
	glBindVertexArray(env->vaos[0]);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);*/
	move_object(&env->objects[0].instances[0], new_v3(0.005, 0, 0));
	draw_object(&env->objects[0], env);
	return (0);
}