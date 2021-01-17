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
#include "../../libft/libft.h"

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

void	print_matrix(float matrix[16])
{
	ft_printf("|%f %f %f %f|\n", matrix[0], matrix[1], matrix[2], matrix[3]);
	ft_printf("|%f %f %f %f|\n", matrix[4], matrix[5], matrix[6], matrix[7]);
	ft_printf("|%f %f %f %f|\n", matrix[8], matrix[9], matrix[10], matrix[11]);
	ft_printf("|%f %f %f %f|\n", matrix[12], matrix[13], matrix[14], matrix[15]);
}