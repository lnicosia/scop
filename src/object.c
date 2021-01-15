/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 22:05:18 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/16 00:14:00 by lnicosia         ###   ########.fr       */
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
	new.name = name;
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
		sizeof(t_instance) * ++env->objects[*count].id)))
		ft_fatal_error("Failed to add object", env);
	(*count)++;
	return (0);
}

int		draw_object(t_object *object, t_env *env)
{
	size_t	count;

	count = 0;
	(void)env;
	while (count < object->count)
	{
		count++;
	}
	return (0);
}