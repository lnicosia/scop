/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 16:38:54 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/21 18:50:05 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"

void	free_objects(t_env *env)
{
	int	i;

	i = 0;
	while (i < MAX_OBJECTS)
	{
		ft_memdel((void**)&env->objects[i].vertices);
		ft_memdel((void**)&env->objects[i].instances);
		ft_memdel((void**)&env->objects[i].indices);
		ft_memdel((void**)&env->objects[i].textures);
		i++;
	}
}

void	free_all(t_env *env)
{
	int	i;

	i = 0;
	while (i < MAX_VAO)
	{
		i++;
	}
	(void)env;
	i = 0;
	while (i < MAX_VBO)
	{
		i++;
	}
	i = 0;
	while (i < MAX_EBO)
	{
		i++;
	}
	i = 0;
	while (i < MAX_SHADERS)
	{
		glDeleteProgram(env->shaders[i]);
		i++;
	}
	glDeleteTextures((int)env->texture_count, env->textures);
	free_objects(env);
	glfwTerminate();
}
