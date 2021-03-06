/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 14:35:01 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/24 15:11:16 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H
# include "libmft.h"

typedef struct	s_camera
{
	float		vfov;
	float		hfov;
	float		ratio;
	float		l;
	float		r;
	float		b;
	float		t;
	float		n;
	float		f;
	float		speed;
	float		yaw;
	float		pitch;
	float		roll;
	t_v3		pos;
	t_v3		front;
	t_v3		up;
	t_v3		right;
}               t_camera;

#endif