/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 17:07:38 by lnicosia          #+#    #+#             */
/*   Updated: 2021/09/20 11:02:17 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include "libft.h"

void	print_object(t_object *object)
{
	ft_printf("%s has %d mesh(es)\n", object->name, object->nb_meshes);
	for (unsigned int i = 0; i < object->nb_meshes; i++)
	{
		print_mesh(&object->meshes[i]);
	}
}

int		draw_all_instances(t_object *object, t_env *env)
{
	for (unsigned int i = 0; i < object->count; i++)
	{
		draw_object(object, i, env);
	}
	return (0);
}

int		draw_object(t_object *object, unsigned int instance, t_env *env)
{
	for (unsigned int i = 0; i < object->nb_meshes; i++)
	{
		draw_mesh(object, &object->meshes[i], instance, env);
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
	ft_printf("'%s' initialized\n", new.name);
	//print_object(&new);
	for (unsigned int i = 0; i < new.nb_meshes; i++)
	{
		new.meshes[i].size = (unsigned int)sizeof(t_vertex) * new.meshes[i].nb_vertices;
		new.meshes[i].name = "";
		new.meshes[i].nb_textures = 1;
		init_mesh_buffers(&new.meshes[i]);
		ft_memdel((void**)&new.meshes[i].vertices);
	}
	new.id = env->object_count;
	env->objects[env->object_count] = new;
	env->object_count++;
	return (0);
}