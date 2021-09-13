/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 17:58:37 by lnicosia          #+#    #+#             */
/*   Updated: 2021/09/13 16:49:37 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUTS_H
# define INPUTS_H
# define MAX_INPUTS 30

enum				e_inputs
{
	MOUSE_LEFT,
	MOUSE_RIGHT,
	ESCAPE,
	ENTER,
	DRAW_MODE,
	LEFT,
	RIGHT,
	UP,
	DOWN,
	RESET,
	CURRENT_TEXTURE,
	LIGHT_MODE,
	ADD_mesh,
	SELECT_mesh_0,
	SELECT_mesh_1,
	SELECT_mesh_2,
	SELECT_mesh_3,
	SELECT_mesh_4,
	SELECT_mesh_5,
	SELECT_mesh_6,
	SELECT_mesh_7,
	SELECT_mesh_8,
	SELECT_mesh_9,
	SELECT_AXE_X,
	SELECT_AXE_Y,
	SELECT_AXE_Z,
	PAGE_UP,
	PAGE_DOWN,
	SHIFT_MOD,
	DRAW_SKYBOX,
};

enum				e_moving_mode
{
	MOVE_CAMERA,
	MOVE_mesh,
};

typedef enum		e_input_states
{
	PRESS,
	RELEASED,
	PRESSED,
	RELEASE,
}					t_input_states;

typedef struct		s_input
{
	int				key1;
	int				key2;
	int				state;
}					t_input;

typedef struct		s_inputs
{
	t_input			escape;
	t_input			enter;
	t_input			draw_mode;
}					t_inputs;

#endif
