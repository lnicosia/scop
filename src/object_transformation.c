/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_transformation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 00:08:55 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/16 00:09:15 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"

int		move_object(t_instance *object, t_v3 move)
{
	object->transform.pos.x += move.x;
	object->transform.pos.y += move.y;
	object->transform.pos.z += move.z;
	return (0);
}

int		rotate_object(t_instance *object, t_v3 rotate)
{
	object->transform.rotation.x += rotate.x;
	object->transform.rotation.y += rotate.y;
	object->transform.rotation.z += rotate.z;
	return (0);
}

int		scale_object(t_instance *object, t_v3 scale)
{
	object->transform.scale.x += scale.x;
	object->transform.scale.y += scale.y;
	object->transform.scale.z += scale.z;
	return (0);
}
