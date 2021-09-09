/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 16:38:54 by lnicosia          #+#    #+#             */
/*   Updated: 2021/09/09 14:31:02 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"

void	free_object(t_object *object)
{
	ft_memdel((void**)&object->vertices);
	ft_memdel((void**)&object->instances);
	ft_memdel((void**)&object->indices);
	glDeleteVertexArrays(1, &object->vao);
	glDeleteBuffers(1, &object->vbo);
	glDeleteBuffers(1, &object->ebo);
}

void	free_objects(t_env *env)
{
	size_t	i;

	i = 0;
	while (i < env->object_count)
	{
		free_object(&env->objects[i]);
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
	glfwDestroyWindow(env->window);
	glfwTerminate();
	ft_printf("Terminate\n");
}
