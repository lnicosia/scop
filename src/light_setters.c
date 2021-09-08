/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_setters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 11:55:49 by lnicosia          #+#    #+#             */
/*   Updated: 2021/09/08 12:14:39 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmft.h"
#include "glad/glad.h"

void	set_ambient(unsigned int shader, t_v3 value)
{
	glUniform3f(glGetUniformLocation(shader, "light.ambient"),
	value.x, value.y, value.z);
}


void	set_specular(unsigned int shader, t_v3 value)
{
	glUniform3f(glGetUniformLocation(shader, "light.specular"),
	value.x, value.y, value.z);
}

void	set_diffuse(unsigned int shader, t_v3 value)
{
	glUniform3f(glGetUniformLocation(shader, "light.diffuse"),
	value.x, value.y, value.z);
}
