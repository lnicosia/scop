/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 12:14:56 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/16 12:43:29 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmft.h"

t_point	new_point(int x, int y)
{
	t_point	new;

	new.x = x;
	new.y = y;
	return (new);
}

t_v2	new_v2(double x, double y)
{
	t_v2	new;

	new.x = x;
	new.y = y;
	return (new);
}

t_v3	new_v3(double x, double y, double z)
{
	t_v3	new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

t_v4	new_v4(double x, double y, double z, double w)
{
	t_v4	new;

	new.x = x;
	new.y = y;
	new.z = z;
	new.w = w;
	return (new);
}

void	reset_mat(float mat[16])
{
	mat[0] = 1.0f;
	mat[1] = 0.0f;
	mat[2] = 0.0f;
	mat[3] = 0.0f;
	mat[4] = 0.0f;
	mat[5] = 1.0f;
	mat[6] = 0.0f;
	mat[7] = 0.0f;
	mat[8] = 0.0f;
	mat[9] = 0.0f;
	mat[10] = 1.0f;
	mat[11] = 0.0f;
	mat[12] = 0.0f;
	mat[13] = 0.0f;
	mat[14] = 0.0f;
	mat[15] = 1.0f;
}