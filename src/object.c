/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 17:07:38 by lnicosia          #+#    #+#             */
/*   Updated: 2021/09/14 10:43:08 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include "libft.h"

int		draw_object(t_object *object, unsigned int instance,
unsigned int shader, t_env *env)
{
	for (unsigned int i = 0; i < object->nb_meshes; i++)
	{
		draw_mesh(object, &object->meshes[i], instance, shader, env);
	}
	return (0);
}

int		init_object(const char *source_file, t_env *env)
{
	t_object	new;

	ft_bzero(&new, sizeof(new));
	if (parse_object(source_file, FULL, &new, env))
		return (custom_error("{yellow}Failed to load %s{reset}\n",
		source_file));
	new.meshes[0].size = (unsigned int)sizeof(t_vertex) * (unsigned int)new.meshes[0].nb_vertices;
	ft_printf("'%s' initialized\n", source_file);
	//print_mesh(&new);
	new.meshes[0].name = "";
	new.meshes[0].nb_textures = 1;
	new.nb_meshes = 1;
	init_mesh_buffers(&new.meshes[0]);
	ft_memdel((void**)&new.meshes[0].vertices);
	new.meshes[0].id = env->object_count;
	env->objects[env->object_count] = new;
	env->object_count++;
	return (0);
}