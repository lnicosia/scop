/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_real_op.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 12:45:55 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/14 22:21:41 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmft.h"

t_complex	ft_radd(double r, t_complex c)
{
	return (ft_cadd(c, new_complex(r, 0)));
}

t_complex	ft_rsub(double r, t_complex c)
{
	return (ft_csub(c, new_complex(r, 0)));
}

t_complex	ft_rmul(double r, t_complex c)
{
	return (ft_cmul(c, new_complex(r, 0)));
}

t_complex	ft_rdiv(double r, t_complex c)
{
	return (ft_cdiv(c, new_complex(r, 0)));
}
