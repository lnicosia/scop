/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 22:05:18 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/17 23:27:03 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include "scop.h"

int		init_object(const char *source_file, const char *name, t_env *env)
{
	t_object	new;

	(void)source_file;
	ft_bzero(&new, sizeof(new));
	new.size = sizeof(float) * 20;
	if (!(new.vertices = (float*)ft_memalloc(new.size)))
		ft_fatal_error("Failed to init object vertices", env);
	new.vertices[0] = 0.5f;
	new.vertices[1] = 0.5f;
	new.vertices[2] = 0.0f;
	new.vertices[3] = 1.0f;
	new.vertices[4] = 1.0f;
	new.vertices[5] = 0.5f;
	new.vertices[6] = -0.5f;
	new.vertices[7] = 0.0f;
	new.vertices[8] = 1.0f;
	new.vertices[9] = 0.0f;
	new.vertices[10] = -0.5f;
	new.vertices[11] = -0.5f;
	new.vertices[12] = 0.0f;
	new.vertices[13] = 0.0f;
	new.vertices[14] = 0.0f;
	new.vertices[15] = -0.5f;
	new.vertices[16] = 0.5f;
	new.vertices[17] = 0.0f;
	new.vertices[18] = 0.0f;
	new.vertices[19] = 1.0f;
	new.center.x = (new.vertices[0] + new.vertices[5] + new.vertices[15]) / 3.0f;
	new.center.y = (new.vertices[1] + new.vertices[6] + new.vertices[16]) / 3.0f;
	new.name = name;
	new.shader = 0;
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

int		draw_object(t_object *object, t_env *env)
{
	size_t	count;

	count = 0;
	glUseProgram(env->shaders[object->shader]);
	while (count < object->count)
	{
		matrix_pipeline(&object->instances[count].transform,
		env->shaders[object->shader], env);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		count++;
	}
	return (0);
}
