/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_parse_bitmasks.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 00:04:53 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/14 01:02:27 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmp_parser.h"

void			print_bits(int32_t nb)
{
	int		i;
	int32_t	save;
	char	buffer[33];

	i = 31;
	save = nb;
	buffer[32] = 0;
	while (i >= 0)
	{
		buffer[31 - i] = (nb & 1) + '0';
		nb = nb >> 1;
		i--;
	}
	ft_printf("%d = |%s|\n", save, buffer);
}

int				get_image_bitmasks_data(unsigned char *str, t_bmp_parser *parser)
{
	parser->alpha_mask = read_int32(str, 0);
	print_bits(parser->alpha_mask);
	parser->green_mask = read_int32(str, 4);
	print_bits(parser->green_mask);
	parser->red_mask = read_int32(str, 8);
	print_bits(parser->red_mask);
	parser->blue_mask = read_int32(str, 12);
	print_bits(parser->blue_mask);
	return (0);
}

int				parse_image_bitmasks(int fd, t_bmp_parser *parser)
{
	int				ret;
	int				size;
	unsigned char	*image_bitmasks;

	size = parser->bpp == 16 ? 3 : 4;
	ft_printf("There are %d different bitmasks\n", size);
	if (!(image_bitmasks = (unsigned char*)ft_memalloc(size * sizeof(int32_t))))
		return (-1);
	if ((ret = read(fd, image_bitmasks, size)) > 0)
	{
		if (get_image_bitmasks_data(image_bitmasks, parser))
		{
			ft_memdel((void**)&image_bitmasks);
			return (custom_error("Image bitmasks are not valid\n"));
		}
	}
	else if (!ret)
	{
		ft_memdel((void**)&image_bitmasks);
		return (custom_error("Incomplete image bitmasks\n"));
	}
	else
	{
		ft_memdel((void**)&image_bitmasks);
		return (custom_error("Error while reading image bitmasks \n"));
	}
	ft_memdel((void**)&image_bitmasks);
	return (0);
}