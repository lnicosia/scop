/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 15:38:54 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/16 17:03:06 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

float	to_radians(float degrees)
{
	return (degrees * ((float)M_PI / 180.0f));
}

float	to_degrees(float radians)
{
	return (radians * (180.0f / (float)M_PI));
}