/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segments_intersect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 10:38:03 by lnicosia          #+#    #+#             */
/*   Updated: 2020/05/01 18:50:23 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Checks if two segments given by 4 points intersect
*/

int		check_parallels(t_v2 v1, t_v2 v2, t_v2 v3, t_v2 v4)
{
	t_v2	vt1;
	t_v2	vt2;

	vt1.x = v2.x - v1.x;
	vt1.y = v2.y - v1.y;
	vt2.x = v4.x - v3.x;
	vt2.y = v4.y - v3.y;
	if ((vt1.x * vt2.y) == (vt1.y * vt2.x))
		return (1);
	return (0);
}

int		segments_intersect(t_v2 v1, t_v2 v2, t_v2 v3, t_v2 v4)
{
	t_v2	intersection;

	intersection = get_intersection(v1, v2, v3, v4);
	if (check_parallels(v1, v2, v3, v4))
		return (0);
	if ((intersection.x <= v1.x && intersection.x <= v2.x)
			|| (intersection.x >= v1.x && intersection.x >= v2.x)
			|| (intersection.y <= v1.y && intersection.y <= v2.y)
			|| (intersection.y >= v1.y && intersection.y >= v2.y)
			|| (intersection.x <= v3.x && intersection.x <= v4.x)
			|| (intersection.x >= v3.x && intersection.x >= v4.x)
			|| (intersection.y <= v3.y && intersection.y <= v4.y)
			|| (intersection.y >= v3.y && intersection.y >= v4.y))
		return (0);
	return (1);
}

/*
**	Checks if two segments intersection on the same line
**	Only works for horizontal and vertical lines
*/

int		check_line_intersection(t_v2 v1, t_v2 v2, t_v2 v3, t_v2 v4)
{
	if (v1.x == v2.x && v2.x == v3.x && v3.x == v4.x)
	{
		if ((v1.y >= v2.y && v2.y >= v3.y && v3.y >= v4.y)
				|| (v1.y <= v2.y && v2.y <= v3.y && v3.y <= v4.y))
			return (0);
		else
		{
			ft_printf("v1.y = %f v2.y = %f v3.y = %f v4.y = %f\n",
					v1.y, v2.y, v3.y, v4.y);
			return (custom_error("Ligne verticale invalide"));
		}
	}
	if (v1.y == v2.y && v2.y == v3.y && v3.y == v4.y)
	{
		if ((v1.x >= v2.x && v2.x >= v3.x && v3.x >= v4.x)
				|| (v1.x <= v2.x && v2.x <= v3.x && v3.x <= v4.x))
			return (0);
		else
			return (custom_error("Ligne horizontal invalide"));
	}
	return (0);
}
