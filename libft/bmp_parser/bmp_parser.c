/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 16:44:23 by sipatry           #+#    #+#             */
/*   Updated: 2021/01/12 13:45:35 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmp_parser.h"
#include <fcntl.h>

static int	parse2(int fd, t_bmp_parser *parser, uint32_t **data)
{
	if (parser->color_used || parser->bpp <= 8)
	{
		if (set_color_table(fd, parser))
			return (custom_error("Error in color table\n"));
	}
	if (parse_pixel_data(fd, parser, data))
		return (custom_error("Error in pixel data\n"));
	return (0);
}

/*
**	Main function: parse every part of the BMP file:
**	-File header
**	-Image header
**	-Image data
*/

static int	parse(int fd, uint32_t **data)
{
	t_bmp_parser	parser;

	if (parse_file_header(fd, &parser))
		return (custom_error("Error in file header\n"));
	if (get_image_header_size(fd, &parser))
		return (custom_error("Error in image header\n"));
	if (parse_image_header(fd, &parser))
		return (custom_error("Error in image header\n"));
	ft_printf("{red}");
	if (!(*data = (uint32_t*)malloc(parser.bpp * parser.w * parser.h)))
		return (ft_perror("Failed to malloc data\n"));
	return (parse2(fd, &parser, data));
}

/*
**	Init function:
**	-Create a new SDL surface to store the image
**	-Open the given file
**	-Parse it
**	-Close the file
*/

int			parse_bmp(char *file, uint32_t **data)
{
	int	fd;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (custom_error("Could not open \"%s\"\n", file));
	if (parse(fd, data))
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
