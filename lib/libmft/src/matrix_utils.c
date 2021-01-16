/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 13:09:27 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/16 12:42:09 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libmft.h"

/*
** Translates vec of the given translation vector
*/

void    translate(float mat[16], t_v3 translation)
{
    mat[3] += translation.x;
    mat[7] += translation.y;
    mat[11] += translation.z;
}

/*
** Scales vec of the given translation vector
*/

void    scale(float mat[16], t_v3 scale)
{
    mat[0] *= scale.x;
    mat[5] *= scale.y;
    mat[10] *= scale.z;
}

/*
** Rotates vec of the given angle on the X-axis
*/

void    rotate_x(float mat[16], double angle)
{
    mat[5] = cos(angle);
    mat[6] = -sin(angle);
    mat[9] = sin(angle);
    mat[10] = cos(angle);
}

/*
** Rotates vec of the given angle on the Y-axis
*/

void    rotate_y(float mat[16], double angle)
{
    mat[0] = cos(angle);
    mat[2] = sin(angle);
    mat[8] = -sin(angle);
    mat[10] = cos(angle);
}

/*
** Rotates vec of the given angle on the Z-axis
*/

void    rotate_z(float mat[16], double angle)
{
    mat[0] = cos(angle);
    mat[1] = -sin(angle);
    mat[8] = sin(angle);
    mat[9] = cos(angle);
}