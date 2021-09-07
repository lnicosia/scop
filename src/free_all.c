/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 16:38:54 by lnicosia          #+#    #+#             */
/*   Updated: 2021/09/07 15:05:03 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"

void	free_objects(t_env *env)
{
	size_t	i;

	i = 0;
	while (i < env->object_count)
	{
		ft_memdel((void**)&env->objects[i].vertices);
		ft_memdel((void**)&env->objects[i].instances);
		ft_memdel((void**)&env->objects[i].indices);
		i++;
	}
}

void	free_texture_names(t_env *env)
{
	for (int i = 0; i < MAX_ACTIVE_TEXTURES; i++)
	{
		if (env->diffuse_names[i])
			ft_memdel((void**)&env->diffuse_names[i]);
	}
}

void	free_all(t_env *env)
{
	size_t	i;

	i = 0;
	while (i < env->vao_count)
	{
		i++;
	}
	(void)env;
	i = 0;
	while (i < env->vbo_count)
	{
		i++;
	}
	i = 0;
	while (i < env->ebo_count)
	{
		i++;
	}
	i = 0;
	while (i < env->shader_count)
	{
		glDeleteProgram(env->shaders[i]);
		i++;
	}
	if (env->texture_count > 0)
		glDeleteTextures((int)env->texture_count, env->textures);
	free_texture_names(env);
	free_objects(env);
	glfwTerminate();
}
