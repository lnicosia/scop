/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 22:05:18 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/18 14:40:09 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include "scop.h"

int		init_object_buffers(t_object *object)
{
	glGenVertexArrays(1, &object->vao);
	glGenBuffers(1, &object->vbo);
	glGenBuffers(1, &object->ebo);
	glBindVertexArray(object->vao);
	glBufferData(GL_ARRAY_BUFFER, object->size, object->vertices,
	GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
	(int)sizeof(*object->indices) * object->nb_indexes, object->indices,
	GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
	(void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
	(void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
	return (0);
}

int		init_object(const char *source_file, unsigned int *textures,
unsigned int nb_textures, t_env *env)
{
	t_object	new;

	(void)source_file;
	(void)textures;
	ft_bzero(&new, sizeof(new));
	new.nb_vertices = 4;
	new.nb_indexes = 6;
	new.size = (unsigned int)sizeof(t_vertex) * (unsigned int)new.nb_vertices;
	if (!(new.vertices = (t_vertex*)ft_memalloc(new.size)))
		ft_fatal_error("Failed to init object vertices", env);
	if (parse_object(source_file, &new))
		return (custom_error("{yellow}Failed to load %s{reset}\n",
		source_file));
	ft_bzero(new.vertices, sizeof(new.size));
	new.vertices[0].pos.x = 0.5f;
	new.vertices[0].pos.y = 0.5f;
	new.vertices[0].pos.z = 0.0f;
	new.vertices[0].text.x = 1.0f;
	new.vertices[0].text.y = 1.0f;
	new.vertices[1].pos.x = 0.5f;
	new.vertices[1].pos.y = -0.5f;
	new.vertices[1].pos.z = 0.0f;
	new.vertices[1].text.x = 1.0f;
	new.vertices[1].text.y = 0.0f;
	new.vertices[2].pos.x = -0.5f;
	new.vertices[2].pos.y = -0.5f;
	new.vertices[2].pos.z = 0.0f;
	new.vertices[2].text.x = 0.0f;
	new.vertices[2].text.y = 0.0f;
	new.vertices[3].pos.x = -0.5f;
	new.vertices[3].pos.y = 0.5f;
	new.vertices[3].pos.z = 0.0f;
	new.vertices[3].text.x = 0.0f;
	new.vertices[3].text.y = 1.0f;
	new.center.x = (new.vertices[0].pos.x + new.vertices[1].pos.x + new.vertices[2].pos.x) / 3.0f;
	new.center.y = (new.vertices[0].pos.y + new.vertices[0].pos.y + new.vertices[0].pos.y) / 3.0f;
	new.name = "";
	new.nb_textures = nb_textures;
	init_object_buffers(&new);
	new.id = env->object_count;
	env->objects[env->object_count] = new;
	env->object_count++;
	return (0);
}

int		add_object(size_t id, t_env *env)
{
	size_t	*count;

	count = &env->objects[id].count;
	if (!(env->objects[id].instances =
		(t_instance*)realloc(env->objects[id].instances,
		sizeof(t_instance) * ++(*count))))
		ft_fatal_error("Failed to add object", env);
	ft_bzero(&env->objects[id].instances[*count - 1],
	sizeof(env->objects[id].instances[*count - 1]));
	env->objects[id].instances[*count - 1].transform.scale = new_v3(1, 1, 1);
	return (0);
}

int		matrix_pipeline(t_transform *transform, unsigned int shader, t_env *env)
{
	reset_matrix(env->matrix);
	translate(env->matrix, transform->pos);
	rotate_x(env->matrix, transform->rotation.x);
	rotate_y(env->matrix, transform->rotation.y);
	rotate_z(env->matrix, transform->rotation.z);
	scale(env->matrix, transform->scale);
	glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_TRUE,
	env->matrix);
	reset_matrix(env->matrix);
	translate(env->matrix, env->camera.pos);
	glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_TRUE,
	env->matrix);
	// Pas besoin de la reset a chaque frame
	glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_TRUE,
	env->projection_matrix);
	return (0);
}

int		draw_object(t_object *object, unsigned int shader, t_env *env)
{
	unsigned int	i;
	size_t			count;

	i = 0;
	count = 0;
	glUseProgram(shader);
	while (i < object->nb_textures)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, object->textures[i]);
		i++;
	}
	glUniform1i(glGetUniformLocation(shader, "texture1"), 0);
	glUniform1i(glGetUniformLocation(shader, "texture2"), 1);
	glBindVertexArray(env->vaos[0]);
	//glBindVertexArray(object->vao);
	while (count < object->count)
	{
		matrix_pipeline(&object->instances[count].transform, shader, env);
		glDrawElements(GL_TRIANGLES, object->nb_indexes, GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		count++;
	}
	glBindVertexArray(0);
	return (0);
}
