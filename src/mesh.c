/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 22:05:18 by lnicosia          #+#    #+#             */
/*   Updated: 2021/09/14 18:27:21 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include "scop.h"

void	print_mesh(t_mesh *mesh)
{
	unsigned int	i;

	ft_printf("%d Vertices:\n", mesh->nb_vertices);
	i = 0;
	while (i < mesh->nb_vertices)
	{
		ft_printf("%9f, %9f, %9f,	%9f, %9f, %9f,	%9f, %9f\n", 
		mesh->vertices[i].pos.x, mesh->vertices[i].pos.y,
		mesh->vertices[i].pos.z, mesh->vertices[i].norm.x,
		mesh->vertices[i].norm.y, mesh->vertices[i].norm.z,
		mesh->vertices[i].text.x, mesh->vertices[i].text.y);
		i++;
	}
	ft_printf("%d Indices:\n", mesh->nb_indices);
	i = 0;
	while (i < mesh->nb_indices)
	{
		ft_printf("%d, %d, %d\n", 
		mesh->indices[i] + 1, mesh->indices[i + 1] + 1,
		mesh->indices[i + 2] + 1);
		i += 3;
	}
}

int		init_mesh_buffers(t_mesh *mesh)
{
	glGenVertexArrays(1, &mesh->vao);
	glGenBuffers(1, &mesh->vbo);
	glGenBuffers(1, &mesh->ebo);
	glBindVertexArray(mesh->vao);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
	glBufferData(GL_ARRAY_BUFFER, mesh->size, mesh->vertices,
	GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
	(int)sizeof(*mesh->indices) * mesh->nb_indices, mesh->indices,
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
	return (0);
}

int		set_object_texture(t_instance *object, int id, unsigned int text)
{
	if (id >= MAX_ACTIVE_TEXTURES)
		return (-1);
	object->textures[id] = text;
	return (0);
}


int		set_mesh_texture(t_mesh *mesh, size_t instance, int id, unsigned int text)
{
	if (id >= MAX_ACTIVE_TEXTURES)
		return (-1);
	mesh->instances[instance].textures[id] = text;
	return (0);
}

int		add_object(size_t id, t_env *env)
{
	size_t	*count;

	if (id >= env->object_count)
		return (custom_error("Tried to add a non existing mesh\n"));
	count = &env->objects[id].count;
	if (!(env->objects[id].instances =
		(t_instance*)realloc(env->objects[id].instances,
		sizeof(t_instance) * ++(*count))))
		ft_fatal_error("Failed to add mesh", env);
	for (unsigned int i = 0; i < env->objects[id].nb_meshes; i++)
	{
		if (!(env->objects[id].meshes[i].instances =
			(t_texture_id*)realloc(env->objects[id].meshes[i].instances,
			sizeof(t_texture_id) * *count)))
			ft_fatal_error("Failed to add mesh", env);
	}
	ft_bzero(&env->objects[id].instances[*count - 1],
	sizeof(env->objects[id].instances[*count - 1]));
	env->objects[id].instances[*count - 1].transform.scale = new_v3(1, 1, 1);
	update_object(&env->objects[id].instances[*count - 1]);
	for (unsigned int i = 0; i < env->objects[id].nb_meshes; i++)
	{
		set_mesh_texture(&env->objects[id].meshes[i], *count - 1, 0, env->textures[env->current_text]);
	}
	return (0);
}

int		matrix_pipeline(float *matrix, unsigned int shader, t_env *env)
{
	glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_TRUE,
	matrix);
	glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_TRUE,
	env->look_at_matrix);
	glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_TRUE,
	env->projection_matrix);
	return (0);
}

int		bind_textures(t_mesh *mesh, unsigned int instance)
{
	size_t	i;

	i = 0;
	while (i < mesh->nb_textures)
	{
		glActiveTexture(GL_TEXTURE0 + (unsigned int)i);
		glBindTexture(GL_TEXTURE_2D, mesh->instances[instance].textures[i]);
		i++;
	}
	return (0);
}

int		draw_mesh(t_object *object, t_mesh *mesh, unsigned int instance,
unsigned int shader, t_env *env)
{
	glUseProgram(shader);
	bind_textures(mesh, instance);
	glBindVertexArray(mesh->vao);
	matrix_pipeline(object->instances[instance].matrix, shader, env);
	glPolygonMode(GL_FRONT_AND_BACK, env->polygon_mode);
	glDrawElements(GL_TRIANGLES, (int)mesh->nb_indices, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	return (0);
}
