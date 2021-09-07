/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 22:05:18 by lnicosia          #+#    #+#             */
/*   Updated: 2021/09/07 15:05:50 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include "scop.h"

void	print_object(t_object *object)
{
	unsigned int	i;

	ft_printf("Vertices:\n");
	i = 0;
	while (i < object->nb_vertices)
	{
		ft_printf("%f, %f, %f,	%f, %f, %f,	%f, %f\n", 
		object->vertices[i].pos.x, object->vertices[i].pos.y,
		object->vertices[i].pos.z, object->vertices[i].norm.x,
		object->vertices[i].norm.y, object->vertices[i].norm.z,
		object->vertices[i].text.x, object->vertices[i].text.y);
		i++;
	}
	ft_printf("Indices:\n");
	i = 0;
	while (i < object->nb_indices)
	{
		ft_printf("%d, %d, %d\n", 
		object->indices[i] + 1, object->indices[i + 1] + 1,
		object->indices[i + 2] + 1);
		i += 3;
	}
}

int		init_object_buffers(t_object *object)
{
	glGenVertexArrays(1, &object->vao);
	glGenBuffers(1, &object->vbo);
	glGenBuffers(1, &object->ebo);
	glBindVertexArray(object->vao);
	glBindBuffer(GL_ARRAY_BUFFER, object->vbo);
	glBufferData(GL_ARRAY_BUFFER, object->size, object->vertices,
	GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
	(int)sizeof(*object->indices) * object->nb_indices, object->indices,
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

int		init_object(const char *source_file, unsigned int *textures,
int nb_textures, t_env *env)
{
	t_object	new;

	ft_bzero(&new, sizeof(new));
	new.textures = textures;
	if (parse_object(source_file, &new, env))
		return (custom_error("{yellow}Failed to load %s{reset}\n",
		source_file));
	new.size = (unsigned int)sizeof(t_vertex) * (unsigned int)new.nb_vertices;
	ft_printf("Object parsed\n");
	//print_object(&new);
	new.name = "";
	new.nb_textures = nb_textures;
	init_object_buffers(&new);
	ft_memdel((void**)&new.vertices);
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
	//translate(env->matrix, env->camera.pos);
	/*rotate_x(env->matrix, env->camera.front.x);
	rotate_y(env->matrix, env->camera.front.y);
	rotate_z(env->matrix, env->camera.front.z);
	translate(env->matrix, env->camera.pos);*/
	//look_at(env->matrix, env->camera.pos,
	//	add_vec(env->camera.pos, env->camera.front), env->camera.up);
	look_at(env->matrix, env->camera.pos,
		env->camera.front, env->camera.up);
	glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_TRUE,
	env->matrix);
	glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_TRUE,
	env->projection_matrix);
	return (0);
}

int		bind_textures(t_object *object, unsigned int shader, t_env *env)
{
	int		i;
	char	*nb;
	char	*name;

	i = 0;
	while (i < object->nb_textures)
	{
		glActiveTexture(GL_TEXTURE0 + (unsigned int)i);
		if (!(nb = ft_itoa(i + 1)))
			ft_fatal_error("Failed to malloc texture number string", env);
		if (!(name = ft_strjoin("material.diffuse", nb)))
			ft_fatal_error("Failed to malloc texture number string", env);
		glUniform1i(glGetUniformLocation(shader, name), i);
		ft_strdel(&name);
		ft_strdel(&nb);
		glBindTexture(GL_TEXTURE_2D, object->textures[i]);
		i++;
	}
	return (0);
}

int		draw_object(t_object *object, unsigned int instance,
unsigned int shader, t_env *env)
{
	glUseProgram(shader);
	bind_textures(object, shader, env);
	glBindVertexArray(object->vao);
	matrix_pipeline(&object->instances[instance].transform, shader, env);
	glPolygonMode(GL_FRONT_AND_BACK, env->polygon_mode);
	glDrawElements(GL_TRIANGLES, (int)object->nb_indices, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	return (0);
}
