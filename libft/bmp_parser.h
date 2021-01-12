/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 13:48:16 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/12 13:45:54 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_PARSER_H
# define BMP_PARSER_H
# define TRUE 1
# define FALSE 0
# include <stdint.h>
# include "libft.h"

typedef struct		s_bmp_parser
{
	unsigned int	*colors;
	int32_t			size;
	int32_t			start;
	int32_t			image_header_size;
	int32_t			w;
	int32_t			h;
	int16_t			planes;
	int16_t			bpp;
	int32_t			compression;
	int32_t			image_size;
	int32_t			xpixels_per_meter;
	int32_t			ypixels_per_meter;
	int32_t			color_used;
	int32_t			color_important;
	int				ret;
	int				index;
	int				skybox_index;
	char			padding[4];
}					t_bmp_parser;

int32_t				read_int32(unsigned char *str, int index);
int32_t				read_int16(unsigned char *str, int index);
int32_t				read_int32_swaped(unsigned char *str, int index);
uint32_t			read_color32(unsigned char *str, int index);
uint32_t			read_color24(unsigned char *str, int index);
uint32_t			read_color16(unsigned char *str, int index);
uint32_t			read_color8(unsigned char *str, int index,
		t_bmp_parser *parser);
uint32_t			read_color4(unsigned char *str, double index,
		unsigned int *colors);
uint32_t			read_color1(unsigned char *str, double index,
		unsigned int *colors);
unsigned int		get_pixel(double byte, unsigned char *str,
t_bmp_parser *parser);
void				check_bmp_parsing(t_bmp_parser parser);
int					parse_file_header(int fd, t_bmp_parser *parser);
int					get_image_header_data(unsigned char *str,
		t_bmp_parser *parser);
int					parse_image_header(int fd, t_bmp_parser *parser);
int					set_color_table(int fd, t_bmp_parser *parser);
int					get_image_header_size(int fd, t_bmp_parser *parser);
int					parse_pixel_data(int fd, t_bmp_parser *parser,
uint32_t **data);
int					set_byte(int *x, int *y, double *byte,
t_bmp_parser *parser);
#endif
