/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 16:38:54 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/12 23:45:37 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	free_all(t_env *env)
{
	(void)env;
	glDeleteVertexArrays(1, &env->tuto_vao);
	glDeleteBuffers(1, &env->tuto_vbo);
	glDeleteBuffers(1, &env->tuto_ebo);
	glDeleteProgram(env->tuto_shader);
	glfwTerminate();
}
