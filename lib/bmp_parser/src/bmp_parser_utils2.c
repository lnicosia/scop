/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_parser_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 16:57:40 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/13 14:25:16 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmp_parser.h"

/*
**	Read a integer of 32 bits
**	TODO Better protection
*/

int32_t		read_int32_swaped(unsigned char *str, int index)
{
	int32_t		res;

	res = str[index + 3] >> 24
		| str[index + 2] >> 16
		| str[index + 1] >> 8
		| str[index + 0];
	return (res);
}

/*
**	Read a integer of 32 bits
**	TODO Better protection
*/

int32_t		read_int32(unsigned char *str, int index)
{
	int32_t		res;

	res = str[index + 3] << 24
		| str[index + 2] << 16
		| str[index + 1] << 8
		| str[index];
	return (res);
}

/*
**	Read a integer of 16 bits
**	TODO Better protection
*/

int32_t		read_int16(unsigned char *str, int index)
{
	int32_t		res;

	res = str[index + 1] << 8
		| str[index];
	return (res);
}

/*
**	Read a integer of 32 bits
**	TODO Better protection
*/

uint32_t	read_color32(unsigned char *str, int index)
{
	uint32_t		res;

	res = str[index + 3] << 24
		| str[index + 2] << 16
		| str[index + 1] << 8
		| str[index + 0];
	return (res);
}

/*
**	Read a integer of 24 bits
**	TODO Better protection
*/

uint32_t	read_color24(unsigned char *str, int index)
{
	uint32_t		res;

	res = str[index + 2] << 16
		| str[index + 1] << 8
		| str[index + 0] << 0;
	return (res);
}
