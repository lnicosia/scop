/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 16:44:23 by sipatry           #+#    #+#             */
/*   Updated: 2021/01/17 23:19:33 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmp_parser.h"
#include <fcntl.h>

static int	parse2(int fd, t_bmp_parser *parser, t_texture *texture)
{
	if (parser->color_used || parser->bpp <= 8)
	{
		if (set_color_table(fd, parser))
			return (custom_error("Error in color table\n"));
	}
	if (parse_pixel_data(fd, parser, texture))
		return (custom_error("Error in pixel data\n"));
	return (0);
}

/*
**	Main function: parse every part of the BMP file:
**	-File header
**	-Image header
**	-Image data
*/

static int	parse(int fd, t_texture *texture)
{
	t_bmp_parser	parser;

	if (parse_file_header(fd, &parser))
		return (custom_error("Error in file header\n"));
	if (get_image_header_size(fd, &parser))
		return (custom_error("Error in image header\n"));
	if (parse_image_header(fd, &parser))
		return (custom_error("Error in image header\n"));
	texture->w = parser.w;
	texture->h = parser.h;
	ft_printf("{red}");
	parser.pixel_bytes = parser.opp * parser.w * parser.h;
	return (parse2(fd, &parser, texture));
}

/*
**	Init function:
**	-Create a new array to store the image
**	-Open the given file
**	-Parse it
**	-Close the file
*/

int			parse_bmp(char *file, t_texture *texture)
{
	int	fd;

	ft_bzero(texture, sizeof(*texture));
	if ((fd = open(file, O_RDONLY)) == -1)
		return (custom_error("Could not open \"%s\"\n", file));
	if (parse(fd, texture))
	{
		if (close(fd))
			return (ft_perror("Bmp parsing failed and could not close the"
			" file\n"));
		return (custom_error("Error while parsing \"%s\"\n", file));
	}
	if (close(fd))
		return (custom_error("Could not close \"%s\"\n", file));
	ft_printf("{reset}");
	return (0);
}
