/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_matrix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 14:48:46 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/16 16:35:08 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

void	projection_matrix(t_camera *camera, float matrix[16])
{
	(void)camera;
	matrix[0] = camera->n / camera->r;
	matrix[1] = 0.0f;
	matrix[2] = 0.0f;
	matrix[3] = 0.0f;
	matrix[4] = 0.0f;
	matrix[5] = camera->n / camera->t;
	matrix[6] = 0.0f;
	matrix[7] = 0.0f;
	matrix[8] = 0.0f;
	matrix[9] = 0.0f;
	matrix[10] = -(camera->f + camera->n) / (camera->f - camera->n);
	matrix[11] = (-2 * camera->f * camera->n) / (camera->f - camera->n);
	matrix[12] = 0.0f;
	matrix[13] = 0.0f;
	matrix[14] = 1.0f;
	matrix[15] = 0.0f;
}