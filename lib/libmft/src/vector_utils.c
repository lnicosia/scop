/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 12:14:56 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/16 17:02:50 by lnicosia         ###   ########.fr       */
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

t_v2	new_v2(float x, float y)
{
	t_v2	new;

	new.x = x;
	new.y = y;
	return (new);
}

t_v3	new_v3(float x, float y, float z)
{
	t_v3	new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

t_v4	new_v4(float x, float y, float z, float w)
{
	t_v4	new;

	new.x = x;
	new.y = y;
	new.z = z;
	new.w = w;
	return (new);
}