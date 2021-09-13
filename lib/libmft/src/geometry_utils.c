/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 16:33:02 by lnicosia          #+#    #+#             */
/*   Updated: 2021/09/10 16:36:40 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmft.h"
#include <math.h>

float	distance_between_points(t_v3 p1, t_v3 p2)
{
	return (sqrtf(
		(p2.x - p1.x) * (p2.x - p1.x) +
		(p2.y - p1.y) * (p2.y - p1.y) +
		(p2.z - p1.z) * (p2.z - p1.z)));
}