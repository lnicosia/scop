/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 15:02:31 by lnicosia          #+#    #+#             */
/*   Updated: 2021/09/16 17:15:45 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include "libft.h"

void			set_textures(t_env *env)
{
	if (ft_strequ(env->objects[1].name, "resources/objects/Spartan/source/Spartan.obj"))
		set_spartan_textures(env);
	if (ft_strequ(env->objects[1].name, "resources/objects/house/house.obj"))
		set_house_textures(env);
	if (ft_strequ(env->objects[1].name, "resources/objects/backpack/backpack.obj"))
		set_object_texture(&env->objects[1], 0, 0, env->textures[5]);
	if (ft_strequ(env->objects[1].name, "resources/objects/swamp-location/source/map_1.obj"))
		set_swamp_textures(env);
}

void			draw_swamp(t_env *env)
{
	for (unsigned int i = 0; i < env->instance_count; i++)
	{
		for (unsigned int j = 0; j < 6; j++)
		{
			draw_mesh(&env->objects[1], &env->objects[1].meshes[j], i,
			env->shaders[env->light_mode], env);
		}
		draw_mesh(&env->objects[1], &env->objects[1].meshes[6], i,
		env->shaders[1], env);
		draw_mesh(&env->objects[1], &env->objects[1].meshes[7], i,
		env->shaders[1], env);
		draw_mesh(&env->objects[1], &env->objects[1].meshes[8], i,
		env->shaders[1], env);
		draw_mesh(&env->objects[1], &env->objects[1].meshes[9], i,
		env->shaders[1], env);
	}
}

void			set_swamp_textures(t_env *env)
{
	set_mesh_texture(&env->objects[1].meshes[0], env->selected_object, 0,
	env->textures[16]); // Terrain
	set_mesh_texture(&env->objects[1].meshes[1], env->selected_object, 0,
	env->textures[19]); // Fontaine
	set_mesh_texture(&env->objects[1].meshes[2], env->selected_object, 0,
	env->textures[19]); // Riviere
	set_mesh_texture(&env->objects[1].meshes[3], env->selected_object, 0,
	env->textures[17]); //
	set_mesh_texture(&env->objects[1].meshes[4], env->selected_object, 0,
	env->textures[19]); // Base du tronc
	set_mesh_texture(&env->objects[1].meshes[5], env->selected_object, 0,
	env->textures[18]); // Objets
	set_mesh_texture(&env->objects[1].meshes[6], env->selected_object, 0,
	env->textures[19]); // Brasero 1
	set_mesh_texture(&env->objects[1].meshes[7], env->selected_object, 0,
	env->textures[19]); // Brasero 2
	set_mesh_texture(&env->objects[1].meshes[8], env->selected_object, 0,
	env->textures[19]); // Brasero arbre
	set_mesh_texture(&env->objects[1].meshes[9], env->selected_object, 0,
	env->textures[19]); // Aura arbre
}

void			set_house_textures(t_env *env)
{
	set_mesh_texture(&env->objects[1].meshes[0], env->selected_object, 0,
	env->textures[7]);
	set_mesh_texture(&env->objects[1].meshes[1], env->selected_object, 0,
	env->textures[0]);
	set_mesh_texture(&env->objects[1].meshes[2], env->selected_object, 0,
	env->textures[7]);
	set_mesh_texture(&env->objects[1].meshes[3], env->selected_object, 0,
	env->textures[8]);
}

void			set_spartan_textures(t_env *env)
{
	set_mesh_texture(&env->objects[1].meshes[0], env->selected_object, 0,
	env->textures[0]);
	set_mesh_texture(&env->objects[1].meshes[1], env->selected_object, 0,
	env->textures[13]);
	set_mesh_texture(&env->objects[1].meshes[2], env->selected_object, 0,
	env->textures[13]);
	set_mesh_texture(&env->objects[1].meshes[3], env->selected_object, 0,
	env->textures[12]);
	set_mesh_texture(&env->objects[1].meshes[4], env->selected_object, 0,
	env->textures[11]);
	set_mesh_texture(&env->objects[1].meshes[5], env->selected_object, 0,
	env->textures[11]);
	set_mesh_texture(&env->objects[1].meshes[6], env->selected_object, 0,
	env->textures[10]);
	set_mesh_texture(&env->objects[1].meshes[7], env->selected_object, 0,
	env->textures[10]);
	set_mesh_texture(&env->objects[1].meshes[8], env->selected_object, 0,
	env->textures[14]);
	set_mesh_texture(&env->objects[1].meshes[9], env->selected_object, 0,
	env->textures[14]);
	set_mesh_texture(&env->objects[1].meshes[10], env->selected_object, 0,
	env->textures[9]);
	set_mesh_texture(&env->objects[1].meshes[11], env->selected_object, 0,
	env->textures[9]);
	set_mesh_texture(&env->objects[1].meshes[12], env->selected_object, 0,
	env->textures[15]);
	set_mesh_texture(&env->objects[1].meshes[13], env->selected_object, 0,
	env->textures[15]);
	set_mesh_texture(&env->objects[1].meshes[14], env->selected_object, 0,
	env->textures[12]);
	set_mesh_texture(&env->objects[1].meshes[15], env->selected_object, 0,
	env->textures[15]);
	set_mesh_texture(&env->objects[1].meshes[16], env->selected_object, 0,
	env->textures[15]);
}