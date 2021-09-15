/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 17:58:37 by lnicosia          #+#    #+#             */
/*   Updated: 2021/09/15 10:10:10 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUTS_H
# define INPUTS_H
# define MAX_INPUTS 31

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
	ADD_OBJECT,
	SELECT_OBJECT_0,
	SELECT_OBJECT_1,
	SELECT_OBJECT_2,
	SELECT_OBJECT_3,
	SELECT_OBJECT_4,
	SELECT_OBJECT_5,
	SELECT_OBJECT_6,
	SELECT_OBJECT_7,
	SELECT_OBJECT_8,
	SELECT_OBJECT_9,
	SELECT_AXE_X,
	SELECT_AXE_Y,
	SELECT_AXE_Z,
	PAGE_UP,
	PAGE_DOWN,
	SHIFT_MOD,
	DRAW_SKYBOX,
	TEXTURE_MODE,
};

enum				e_moving_mode
{
	MOVE_CAMERA,
	MOVE_OBJECT,
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

#endif
