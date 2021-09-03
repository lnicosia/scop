/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 17:58:37 by lnicosia          #+#    #+#             */
/*   Updated: 2021/09/01 16:22:04 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUTS_H
# define INPUTS_H
# define MAX_INPUTS 10

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
	TEXTURE,
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
