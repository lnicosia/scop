/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 12:25:19 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/24 14:24:56 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmft.h"
#include <math.h>

t_v3	normalize(t_v3 vec)
{
	float	length;

	length = sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	vec.x = vec.x / length;
	vec.y = vec.y / length;
	vec.z = vec.z / length;
	return (vec);
}

t_v3	dot_product(t_v3 v1, t_v3 v2)
{
	(void)v1;
	(void)v2;
	return (v1);
}

t_v3	cross_product(t_v3 v1, t_v3 v2)
{
	t_v3 res;

	res.x = v1.y * v2.z - v1.z * v2.y;
	res.y = v1.z * v2.x - v1.x * v2.z;
	res.z = v1.x * v2.y - v1.y * v2.x;
	return (res);
}

t_v3	add_vec(t_v3 v1, t_v3 v2)
{
	return (new_v3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z));
}

t_v3	sub_vec(t_v3 v1, t_v3 v2)
{
	return (new_v3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z));
}

t_v3	mult_vec(t_v3 vec, float mult)
{
	return (new_v3(vec.x * mult, vec.y * mult, vec.z * mult));
}