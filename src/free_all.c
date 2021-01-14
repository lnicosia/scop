/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 16:38:54 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/14 21:28:07 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	free_all(t_env *env)
{
	int	i;

	i = 0;
	while (i < MAX_VAO)
	{
		glDeleteVertexArrays(1, &env->vaos[i]);
		i++;
	}
	(void)env;
	i = 0;
	while (i < MAX_VBO)
	{
		glDeleteBuffers(1, &env->vbos[i]);
		i++;
	}
	i = 0;
	while (i < MAX_EBO)
	{
		glDeleteBuffers(1, &env->ebos[i]);
		i++;
	}
	i = 0;
	while (i < MAX_SHADERS)
	{
		glDeleteProgram(env->shaders[i]);
		i++;
	}
	glfwTerminate();
}
