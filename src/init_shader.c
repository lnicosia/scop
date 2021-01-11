/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 19:30:44 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/11 19:42:22 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"

int		init_pipeline_shader(GLenum type, const char *source, t_env *env)
{
	unsigned int	shader;

	shader = glCreateShader(type);
	if (shader == 0)
		return (custom_error("Failed to create empty \"\" shader\n"));
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);
	env->success = GL_FALSE;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &env->success);
	if (env->success != GL_TRUE)
		return (custom_error("Failed to compiled \"\" shader\n"));
	return (0);
}
