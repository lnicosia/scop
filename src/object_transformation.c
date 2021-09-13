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

void	update_mesh(t_instance *mesh)
{
	reset_matrix(mesh->matrix);
	translate(mesh->matrix, mesh->transform.pos);
	rotate_along_axis(mesh->matrix, new_v3(1.0f, 0.0f, 0.0f), mesh->transform.rotation.x);
	rotate_along_axis(mesh->matrix, new_v3(0.0f, 1.0f, 0.0f), mesh->transform.rotation.y);
	rotate_along_axis(mesh->matrix, new_v3(0.0f, 0.0f, 1.0f), mesh->transform.rotation.z);
	scale(mesh->matrix, mesh->transform.scale);
}

int		move_mesh(t_instance *mesh, t_v3 move)
{
	mesh->transform.pos.x += move.x;
	mesh->transform.pos.y += move.y;
	mesh->transform.pos.z += move.z;
	update_mesh(mesh);
	return (0);
}

int		rotate_mesh(t_instance *mesh, t_v3 rotate)
{
	mesh->transform.rotation.x += rotate.x;
	mesh->transform.rotation.y += rotate.y;
	mesh->transform.rotation.z += rotate.z;
	update_mesh(mesh);
	return (0);
}

int		scale_mesh(t_instance *mesh, t_v3 scale)
{
	mesh->transform.scale.x += scale.x;
	mesh->transform.scale.y += scale.y;
	mesh->transform.scale.z += scale.z;
	update_mesh(mesh);
	return (0);
}
