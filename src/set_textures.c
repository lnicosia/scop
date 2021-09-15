/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 15:02:31 by lnicosia          #+#    #+#             */
/*   Updated: 2021/09/15 16:52:37 by lnicosia         ###   ########.fr       */
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

void			set_swamp_textures(t_env *env)
{
	set_mesh_texture(&env->objects[1].meshes[0], env->selected_object, 0,
	env->textures[16]);
	set_mesh_texture(&env->objects[1].meshes[1], env->selected_object, 0,
	env->textures[19]);
	set_mesh_texture(&env->objects[1].meshes[2], env->selected_object, 0,
	env->textures[19]);
	set_mesh_texture(&env->objects[1].meshes[3], env->selected_object, 0,
	env->textures[17]);
	set_mesh_texture(&env->objects[1].meshes[4], env->selected_object, 0,
	env->textures[19]);
	set_mesh_texture(&env->objects[1].meshes[5], env->selected_object, 0,
	env->textures[18]);
	set_mesh_texture(&env->objects[1].meshes[6], env->selected_object, 0,
	env->textures[19]);
	set_mesh_texture(&env->objects[1].meshes[7], env->selected_object, 0,
	env->textures[19]);
	set_mesh_texture(&env->objects[1].meshes[8], env->selected_object, 0,
	env->textures[19]);
	set_mesh_texture(&env->objects[1].meshes[9], env->selected_object, 0,
	env->textures[19]);
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