/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrixrix_tranformatrixions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 13:09:27 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/16 14:48:00 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libmft.h"

/*
** Translates vec of the given translation vector
*/

void    translate(float matrix[16], t_v3 translation)
{
    matrix[3] += translation.x;
    matrix[7] += translation.y;
    matrix[11] += translation.z;
}

/*
** Scales vec of the given translation vector
*/

void    scale(float matrix[16], t_v3 scale)
{
    matrix[0] *= scale.x;
    matrix[5] *= scale.y;
    matrix[10] *= scale.z;
}

/*
** Rotates vec of the given angle on the X-axis
*/

void    rotate_x(float matrix[16], float angle)
{
    matrix[5] = cosf(angle);
    matrix[6] = -sinf(angle);
    matrix[9] = sinf(angle);
    matrix[10] = cosf(angle);
}

/*
** Rotates vec of the given angle on the Y-axis
*/

void    rotate_y(float matrix[16], float angle)
{
    float   tmp[16];

    reset_matrix(tmp);
    tmp[0] = cosf(angle);
    tmp[2] = sinf(angle);
    tmp[8] = -sinf(angle);
    tmp[10] = cosf(angle);
    mult_matrix(matrix, tmp, matrix);
}

/*
** Rotates vec of the given angle on the Z-axis
*/

void    rotate_z(float matrix[16], float angle)
{
    float   tmp[16];

    reset_matrix(tmp);
    tmp[0] = cosf(angle);
    tmp[1] = -sinf(angle);
    tmp[4] = sinf(angle);
    tmp[5] = cosf(angle);
    mult_matrix(matrix, tmp, matrix);
}

void    rotate_along_axis(float matrix[16], t_v3 axis, float angle)
{
    float   tmp[16];

    tmp[0] = cosf(angle) + axis.x * axis.x * (1 - cosf(angle));
    tmp[1] = axis.x * axis.y * (1 - cosf(angle)) - axis.z * sinf(angle);
    tmp[2] = axis.x * axis.z * (1 - cosf(angle)) + axis.y * sinf(angle);
    tmp[3] = 0;
    tmp[4] = axis.y * axis.x * (1 - cosf(angle)) + axis.z * sinf(angle);
    tmp[5] = cosf(angle) + axis.y * axis.y * (1 - cosf(angle));
    tmp[6] = axis.y * axis.z * (1 - cosf(angle)) - axis.x * sinf(angle);
    tmp[7] = 0;
    tmp[8] = axis.z * axis.x * (1 - cosf(angle)) - axis.y * sinf(angle);
    tmp[9] = axis.z * axis.y * (1 - cosf(angle)) - axis.x * sinf(angle);
    tmp[10] = cosf(angle) + axis.z * axis.z * (1 - cosf(angle));
    tmp[11] = 0;
    tmp[12] = 0;
    tmp[13] = 0;
    tmp[14] = 0;
    tmp[15] = 1;
    mult_matrix(matrix, tmp, matrix);
}