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

void    rotate_x(float matrix[16], double angle)
{
    matrix[5] *= cos(angle);
    matrix[6] *= -sin(angle);
    matrix[9] *= sin(angle);
    matrix[10] *= cos(angle);
}

/*
** Rotates vec of the given angle on the Y-axis
*/

void    rotate_y(float matrix[16], double angle)
{
    matrix[0] *= cos(angle);
    matrix[2] *= sin(angle);
    matrix[8] *= -sin(angle);
    matrix[10] *= cos(angle);
}

/*
** Rotates vec of the given angle on the Z-axis
*/

void    rotate_z(float matrix[16], double angle)
{
    matrix[0] *= cos(angle);
    matrix[1] *= -sin(angle);
    matrix[4] *= sin(angle);
    matrix[5] *= cos(angle);
}