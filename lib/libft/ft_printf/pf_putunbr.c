/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 20:09:15 by lnicosia          #+#    #+#             */
/*   Updated: 2019/02/18 10:24:18 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "put_padding.h"

static void	pf_putulong(unsigned long nb, t_data *data)
{
	char	c;

	if (nb < 10)
	{
		c = '0' + nb;
		fill_buffer(data, &c, 1);
	}
	else
	{
		pf_putulong(nb / 10, data);
		pf_putulong(nb % 10, data);
	}
}

static void	set_padding(t_data *data, unsigned long nb)
{
	data->padding.size = 0;
	if (nb == 0 && data->prec != 0)
		data->padding.size = 1;
	while (nb != 0)
	{
		data->padding.size++;
		nb /= 10;
	}
	data->padding.zeros = 0;
	if (data->prec != -1)
		data->padding.zeros = data->prec - data->padding.size;
	else if (!data->left && data->zero)
		data->padding.zeros = data->l_min - data->padding.size;
	if (data->padding.zeros < 0)
		data->padding.zeros = 0;
	data->padding.right_spaces = 0;
	data->padding.left_spaces = 0;
	if (data->left)
		data->padding.right_spaces = data->l_min - data->padding.zeros
			- data->padding.size;
	else
		data->padding.left_spaces = data->l_min - data->padding.zeros
			- data->padding.size;
}

void		pf_putunbr(t_data *data)
{
	unsigned long	nb;

	nb = va_arg(data->ap, unsigned long);
	if (data->size == 1)
		nb = (unsigned char)nb;
	else if (data->size == 2)
		nb = (unsigned int)nb;
	else if (data->size == 4)
		nb = (unsigned int)nb;
	set_padding(data, nb);
	put_left_spaces(data);
	put_zeros(data);
	if (nb != 0 || data->prec != 0)
		pf_putulong(nb, data);
	put_right_spaces(data);
}
