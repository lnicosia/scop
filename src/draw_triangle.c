/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_triangle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 12:28:54 by lnicosia          #+#    #+#             */
/*   Updated: 2021/09/20 11:04:33 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include "scop.h"
#include <math.h>

int		draw_triangle(t_env *env)
{
	//move_mesh(&env->meshs[0].instances[0], new_v3(0.0f, 0.0f, 0.01f));
	//rotate_mesh(&env->meshs[0].instances[0], new_v3(0.0f, 0.0f, 0.01f));
	//rotate_mesh(&env->meshs[0].instances[0], new_v3(0.0f, 0.01f, 0.0f));
	//scale_mesh(&env->meshs[0].instances[0], new_v3(0.0f, 0.0f, 0.1f));
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	draw_object(&env->objects[0], 0, env);
	return (0);
}