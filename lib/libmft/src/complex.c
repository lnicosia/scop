/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 17:05:34 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/14 22:20:54 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmft.h"
#include <math.h>

t_complex	ft_cconj(t_complex c)
{
	c.i = -c.i;
	return (c);
}

t_complex	new_complex(double r, double i)
{
	t_complex	res;

	res.r = r;
	res.i = i;
	return (res);
}

t_complex	ft_csin(t_complex c)
{
	t_complex	res;

	res.r = sin(c.r) * cosh(c.i);
	res.i = sinh(c.i) * cos(c.r);
	return (res);
}

t_complex	ft_ccos(t_complex c)
{
	t_complex	res;

	res.r = cos(c.r) * cosh(c.i);
	res.i = -sinh(c.r) * sinh(c.r);
	return (res);
}
