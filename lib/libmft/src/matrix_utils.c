/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 13:09:27 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/15 13:23:42 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libmft.h"

/*
** Translates vec of the given translation vector
*/

t_v4    translate(t_v4 vec, t_v3 translation)
{
    vec.x += translation.x;
    vec.y += translation.y;
    vec.z += translation.z;
    return (vec);
}

/*
** Scales vec of the given translation vector
*/

t_v4    scale(t_v4 vec, t_v3 scale)
{
    vec.x *= scale.x;
    vec.y *= scale.y;
    vec.z *= scale.z;
    return (vec);
}

/*
** Rotates vec of the given angle on the X-axis
*/

t_v4    rotate_x(t_v4 vec, double angle)
{
    vec.y = cos(angle) * vec.y - sin(angle) * vec.z;
    vec.z = sin(angle) * vec.y + cos(angle) * vec.z;
    return (vec);
}

/*
** Rotates vec of the given angle on the Y-axis
*/

t_v4    rotate_y(t_v4 vec, double angle)
{
    vec.x = cos(angle) * vec.x + sin(angle) * vec.z;
    vec.z = -sin(angle) * vec.x + cos(angle) * vec.z;
    return (vec);
}

/*
** Rotates vec of the given angle on the Z-axis
*/

t_v4    rotate_z(t_v4 vec, double angle)
{
    vec.x = cos(angle) * vec.x - sin(angle) * vec.y;
    vec.y = sin(angle) * vec.x + cos(angle) * vec.y;
    return (vec);
}