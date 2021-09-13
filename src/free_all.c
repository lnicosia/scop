/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 16:38:54 by lnicosia          #+#    #+#             */
/*   Updated: 2021/09/13 16:49:37 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"

void	free_mesh(t_mesh *mesh)
{
	ft_memdel((void**)&mesh->vertices);
	ft_memdel((void**)&mesh->instances);
	ft_memdel((void**)&mesh->indices);
	glDeleteVertexArrays(1, &mesh->vao);
	glDeleteBuffers(1, &mesh->vbo);
	glDeleteBuffers(1, &mesh->ebo);
}

void	free_meshs(t_env *env)
{
	size_t	i;

	i = 0;
	while (i < env->mesh_count)
	{
		free_mesh(&env->meshs[i]);
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
	i = 0;
	while (i < env->cubemap_count)
	{
		glDeleteTextures(1, &env->cubemaps[i].id);
		i++;
	}
	if (env->texture_count > 0)
		glDeleteTextures((int)env->texture_count, env->textures);
	free_texture_names(env);
	free_meshs(env);
	glfwDestroyWindow(env->window);
	glfwTerminate();
	ft_printf("Terminate\n");
}
