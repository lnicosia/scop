/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 12:14:56 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/16 14:47:39 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmft.h"
#include <math.h>

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