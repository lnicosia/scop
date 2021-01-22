/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrixrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 14:47:31 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/16 14:49:08 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libmft.h"
#include "../../libft/includes/libft.h"

void	reset_matrix(float matrix[16])
{
	//float	angle = to_radians(180);
	matrix[0] = 1.0f;//cosf(angle);
	matrix[1] = 0.0f;//-sinf(angle);
	matrix[2] = 0.0f;
	matrix[3] = 0.0f;
	matrix[4] = 0.0f;//sinf(angle);
	matrix[5] = 1.0f;//cosf(angle);
	matrix[6] = 0.0f;
	matrix[7] = 0.0f;
	matrix[8] = 0.0f;
	matrix[9] = 0.0f;//sinf(angle);
	matrix[10] = 1.0f;//cosf(angle);
	matrix[11] = 0.0f;
	matrix[12] = 0.0f;
	matrix[13] = 0.0f;
	matrix[14] = 0.0f;
	matrix[15] = 1.0f;
}

void	copy_matrix(float dest[16], float src[16])
{
	int	i;

	i = 0;
	while (i < 16)
	{
		dest[i] = src[i];
		i++;
	}
}

void	mult_matrix(float a[16], float b[16], float res[16])
{
	float	tmp[16];

	tmp[0] = a[0] * b[0] + a[1] * b[4] + a[2] * b[8] + a[3] * b[12];
	tmp[1] = a[0] * b[1] + a[1] * b[5] + a[2] * b[9] + a[3] * b[13];
	tmp[2] = a[0] * b[2] + a[1] * b[6] + a[2] * b[10] + a[3] * b[14];
	tmp[3] = a[0] * b[3] + a[1] * b[7] + a[2] * b[11] + a[3] * b[15];
	tmp[4] = a[4] * b[0] + a[5] * b[4] + a[6] * b[8] + a[7] * b[12];
	tmp[5] = a[4] * b[1] + a[5] * b[5] + a[6] * b[9] + a[7] * b[13];
	tmp[6] = a[4] * b[2] + a[5] * b[6] + a[6] * b[10] + a[7] * b[14];
	tmp[7] = a[4] * b[3] + a[5] * b[7] + a[6] * b[11] + a[7] * b[15];
	tmp[8] = a[8] * b[0] + a[9] * b[4] + a[10] * b[8] + a[11] * b[12];
	tmp[9] = a[8] * b[1] + a[9] * b[5] + a[10] * b[9] + a[11] * b[13];
	tmp[10] = a[8] * b[2] + a[9] * b[6] + a[10] * b[10] + a[11] * b[14];
	tmp[11] = a[8] * b[3] + a[9] * b[7] + a[10] * b[11] + a[11] * b[15];
	tmp[12] = a[12] * b[0] + a[13] * b[4] + a[14] * b[8] + a[15] * b[12];
	tmp[13] = a[12] * b[1] + a[13] * b[5] + a[14] * b[9] + a[15] * b[13];
	tmp[14] = a[12] * b[2] + a[13] * b[6] + a[14] * b[10] + a[15] * b[14];
	tmp[15] = a[12] * b[3] + a[13] * b[7] + a[14] * b[11] + a[15] * b[15];
	copy_matrix(res, tmp);
}

void	print_matrix(float matrix[16])
{
	ft_printf("|%f %f %f %f|\n", matrix[0], matrix[1], matrix[2], matrix[3]);
	ft_printf("|%f %f %f %f|\n", matrix[4], matrix[5], matrix[6], matrix[7]);
	ft_printf("|%f %f %f %f|\n", matrix[8], matrix[9], matrix[10], matrix[11]);
	ft_printf("|%f %f %f %f|\n", matrix[12], matrix[13], matrix[14], matrix[15]);
}