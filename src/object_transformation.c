/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_transformation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 00:08:55 by lnicosia          #+#    #+#             */
/*   Updated: 2021/09/08 11:01:58 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"

void	update_object(t_instance *object)
{
	reset_matrix(object->matrix);
	translate(object->matrix, object->transform.pos);
	rotate_along_axis(object->matrix, new_v3(1.0f, 0.0f, 0.0f), object->transform.rotation.x);
	rotate_along_axis(object->matrix, new_v3(0.0f, 1.0f, 0.0f), object->transform.rotation.y);
	rotate_along_axis(object->matrix, new_v3(0.0f, 0.0f, 1.0f), object->transform.rotation.z);
	scale(object->matrix, object->transform.scale);
}

int		move_object(t_instance *object, t_v3 move)
{
	object->transform.pos.x += move.x;
	object->transform.pos.y += move.y;
	object->transform.pos.z += move.z;
	update_object(object);
	return (0);
}

int		rotate_object(t_instance *object, t_v3 rotate)
{
	object->transform.rotation.x += rotate.x;
	object->transform.rotation.y += rotate.y;
	object->transform.rotation.z += rotate.z;
	update_object(object);
	return (0);
}

int		scale_object(t_instance *object, t_v3 scale)
{
	object->transform.scale.x += scale.x;
	object->transform.scale.y += scale.y;
	object->transform.scale.z += scale.z;
	update_object(object);
	return (0);
}
