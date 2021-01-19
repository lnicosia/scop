/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_triangle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 12:28:54 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/19 12:31:17 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include "scop.h"
#include <math.h>

int		draw_triangle(t_env *env)
{
	//move_object(&env->objects[0].instances[0], new_v3(0.0f, 0.0f, 0.01f));
	//rotate_object(&env->objects[0].instances[0], new_v3(0.0f, 0.0f, 0.01f));
	rotate_object(&env->objects[0].instances[0], new_v3(0.01f, 0.0f, 0.0f));
	//scale_object(&env->objects[0].instances[0], new_v3(0.0f, 0.0f, 0.1f));
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	draw_object(&env->objects[0], env->shaders[0], env);
	return (0);
}