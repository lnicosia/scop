/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 15:02:31 by lnicosia          #+#    #+#             */
/*   Updated: 2021/09/21 10:13:57 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include "libft.h"

void	set_all_instances_shader(t_object *object, unsigned int shader)
{
	for (unsigned int i = 0; i < object->nb_meshes; i++)
	{
		for (unsigned int j = 0; j < object->count; j++)
		{
			object->meshes[i].instances[j].shader = shader;
		}
	}
}

void	set_object_shader(t_object *object, unsigned int instance,
unsigned int shader)
{
	for (unsigned int i = 0; i < object->nb_meshes; i++)
	{
		object->meshes[i].instances[instance].shader = shader;
	}
}

void	set_textures(t_env *env)
{
	if (env->objects[1].instances[env->selected_object].texture_mode == SINGLE_TEXTURE)
	{
		set_object_shader(&env->objects[1], env->selected_object, env->shaders[env->light_mode]);
		set_object_texture(&env->objects[1], env->selected_object,
		0, env->textures[env->objects[1].instances[env->selected_object].current_text]);
	}
	else if (env->objects[1].instances[env->selected_object].texture_mode == MULTIPLE_TEXTURES)
	{
		set_object_shader(&env->objects[1], env->selected_object, env->shaders[env->light_mode]);
		if (ft_strequ(env->objects[1].name, "resources/objects/Spartan/source/Spartan.obj"))
			set_spartan_textures(env);
		if (ft_strequ(env->objects[1].name, "resources/objects/backpack/backpack.obj"))
			set_object_texture(&env->objects[1], env->selected_object, 0, env->textures[5]);
		if (ft_strequ(env->objects[1].name, "resources/objects/swamp-location/source/map_1.obj"))
			set_swamp_textures(env);
		if (ft_strequ(env->objects[1].name, "resources/objects/goreforged-greatsword/source/sword.obj"))
			set_object_texture(&env->objects[1], env->selected_object, 0, env->textures[17]);
	}
	else
	{
		set_object_shader(&env->objects[1], env->selected_object, env->shaders[4 + env->light_mode]);
	}
}

void	set_swamp_textures(t_env *env)
{
	for (unsigned int j = 0; j < 6; j++)
	{
		env->objects[1].meshes[j].instances[env->selected_object].shader =
		env->shaders[env->light_mode];
	}
	for (unsigned int j = 6; j < 10; j++)
	{
		env->objects[1].meshes[j].instances[env->selected_object].shader =
		env->shaders[1];
	}
	set_mesh_texture(&env->objects[1].meshes[0], env->selected_object, 0,
	env->textures[13]); // Terrain
	set_mesh_texture(&env->objects[1].meshes[1], env->selected_object, 0,
	env->textures[16]); // Fontaine
	set_mesh_texture(&env->objects[1].meshes[2], env->selected_object, 0,
	env->textures[16]); // Riviere
	set_mesh_texture(&env->objects[1].meshes[3], env->selected_object, 0,
	env->textures[14]); //
	set_mesh_texture(&env->objects[1].meshes[4], env->selected_object, 0,
	env->textures[16]); // Base du tronc
	set_mesh_texture(&env->objects[1].meshes[5], env->selected_object, 0,
	env->textures[15]); // Objets
	set_mesh_texture(&env->objects[1].meshes[6], env->selected_object, 0,
	env->textures[16]); // Brasero 1
	set_mesh_texture(&env->objects[1].meshes[7], env->selected_object, 0,
	env->textures[16]); // Brasero 2
	set_mesh_texture(&env->objects[1].meshes[8], env->selected_object, 0,
	env->textures[16]); // Brasero arbre
	set_mesh_texture(&env->objects[1].meshes[9], env->selected_object, 0,
	env->textures[16]); // Aura arbre
}

void	set_spartan_textures(t_env *env)
{
	set_mesh_texture(&env->objects[1].meshes[0], env->selected_object, 0,
	env->textures[0]);
	set_mesh_texture(&env->objects[1].meshes[1], env->selected_object, 0,
	env->textures[10]);
	set_mesh_texture(&env->objects[1].meshes[2], env->selected_object, 0,
	env->textures[10]);
	set_mesh_texture(&env->objects[1].meshes[3], env->selected_object, 0,
	env->textures[9]);
	set_mesh_texture(&env->objects[1].meshes[4], env->selected_object, 0,
	env->textures[8]);
	set_mesh_texture(&env->objects[1].meshes[5], env->selected_object, 0,
	env->textures[8]);
	set_mesh_texture(&env->objects[1].meshes[6], env->selected_object, 0,
	env->textures[7]);
	set_mesh_texture(&env->objects[1].meshes[7], env->selected_object, 0,
	env->textures[7]);
	set_mesh_texture(&env->objects[1].meshes[8], env->selected_object, 0,
	env->textures[11]);
	set_mesh_texture(&env->objects[1].meshes[9], env->selected_object, 0,
	env->textures[11]);
	set_mesh_texture(&env->objects[1].meshes[10], env->selected_object, 0,
	env->textures[6]);
	set_mesh_texture(&env->objects[1].meshes[11], env->selected_object, 0,
	env->textures[6]);
	set_mesh_texture(&env->objects[1].meshes[12], env->selected_object, 0,
	env->textures[12]);
	set_mesh_texture(&env->objects[1].meshes[13], env->selected_object, 0,
	env->textures[12]);
	set_mesh_texture(&env->objects[1].meshes[14], env->selected_object, 0,
	env->textures[9]);
	set_mesh_texture(&env->objects[1].meshes[15], env->selected_object, 0,
	env->textures[12]);
	set_mesh_texture(&env->objects[1].meshes[16], env->selected_object, 0,
	env->textures[12]);
}