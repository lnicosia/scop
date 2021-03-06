/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_intersection_line_plane.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 16:31:10 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/24 12:42:27 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmft.h"

float	dot_product2(t_v3 a, t_v3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_v3	scale_vector(float l, t_v3 b)
{
	return (new_v3(l * b.x, l * b.y, l * b.z));
}

t_v3	sub_vectors(t_v3 a, t_v3 b)
{
	return (new_v3(a.x - b.x, a.y - b.y, a.z - b.z));
}

t_v3	add_vectors(t_v3 a, t_v3 b)
{
	return (new_v3(a.x + b.x, a.y + b.y, a.z + b.z));
}

t_v3	get_intersection_line_plane(t_v3 p1, t_v3 p2, t_plane plane,
t_v3 plane_point)
{
	t_v3	res;
	t_v3	line;
	t_v3	diff;

	line = sub_vectors(p2, p1);
	if (dot_product2(line, plane.norm) == 0)
		return (new_v3(0, 0, 0));
	diff = sub_vectors(p1, plane_point);
	res = add_vectors(add_vectors(diff, plane_point),
	scale_vector(-dot_product2(diff, plane.norm) / dot_product2(line, plane.norm),
	line));
	return (res);
}
