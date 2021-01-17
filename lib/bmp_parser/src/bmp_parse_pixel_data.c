/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_parse_pixel_data.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 16:56:33 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/17 23:19:19 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmp_parser.h"
#include <math.h>

int		fill_pixel(unsigned char *str, t_bmp_parser *parser,
t_texture *texture, int byte)
{
	int	filler;

	filler = 0;
	while (filler < parser->opp)
	{
		texture->pixels[byte + filler] = str[byte + filler];
		filler++;
	}
	texture->pixels[byte] = str[byte + 2];
	texture->pixels[byte + 1] = str[byte + 1];
	texture->pixels[byte + 2] = str[byte + 0];
	if (filler == 4)
		texture->pixels[byte + 3] = str[byte + 3];
	return (0);
}

/*
** Fills the current pixel array pixel by pixel
** Advances of file's byte ber pixel every iteration
** and fills the last bytes with the pixel data reversed
*/

int		parse_pixels(unsigned char *str, t_bmp_parser *parser,
t_texture *texture)
{
	int	byte;

	byte = 0;
	while (byte < parser->ret)
	{
		fill_pixel(str, parser, texture, byte);
		byte += parser->opp;
	}
	return (0);
}

int		set_byte(int *x, int *y, double *byte, t_bmp_parser *parser)
{
	double	trash;

	if (*x >= parser->w)
	{
		while (modf(*byte, &trash) != 0)
			(*byte) += parser->opp;
		while ((int)*byte % parser->opp != 0)
			(*byte)++;
		*x = 0;
		(*y)--;
	}
	return (0);
}

int		parse_pixel_data(int fd, t_bmp_parser *parser, t_texture *texture)
{
	int				size;
	unsigned char	*str;

	ft_printf("{cyan}");
	if (parser->image_size)
		size = parser->image_size;
	else
		size = ceil((parser->w * parser->bpp) / 32.0) * 4 * parser->h;
	if (!(str = (unsigned char*)ft_memalloc(sizeof(unsigned char) * size)))
		return (ft_perror("Could not malloc buffer for pixel data\n"));
	if ((parser->ret = read(fd, str, size)) > 0)
	{
		if (!(texture->pixels = (unsigned char*)ft_memalloc(parser->ret)))
			return (ft_perror("Failed to malloc data\n"));
		parse_pixels(str, parser, texture);
	}
	ft_memdel((void**)&str);
	return (0);
}
