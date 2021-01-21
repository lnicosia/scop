/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 12:58:23 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/21 14:10:00 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include "libft.h"
#include "inputs.h"

int		init_inputs(t_input *inputs)
{
	size_t	i;

	i = 0;
	while (i < MAX_INPUTS)
	{
		inputs[i].key1 = GLFW_KEY_UNKNOWN;
		inputs[i].key2 = GLFW_KEY_UNKNOWN;
		inputs[i].state = REST;
		i++;
	}	
	inputs[DRAW_MODE].key1 = GLFW_KEY_M;
	inputs[ESCAPE].key1 = GLFW_KEY_ESCAPE;
	inputs[LEFT].key1 = GLFW_KEY_A;
	inputs[LEFT].key2 = GLFW_KEY_LEFT;
	inputs[RIGHT].key1 = GLFW_KEY_D;
	inputs[RIGHT].key2 = GLFW_KEY_RIGHT;
	inputs[UP].key1 = GLFW_KEY_W;
	inputs[UP].key2 = GLFW_KEY_UP;
	inputs[DOWN].key1 = GLFW_KEY_S;
	inputs[DOWN].key2 = GLFW_KEY_DOWN;
	return (0);
}

enum e_input_states		update_input_state(t_input input, t_env *env)
{
	if ((input.key1 != GLFW_KEY_UNKNOWN &&
		glfwGetKey(env->window, input.key1) == GLFW_PRESS)
		|| (input.key2 != GLFW_KEY_UNKNOWN
		&& glfwGetKey(env->window, input.key2) == GLFW_PRESS))
		return (PRESSED);
	if (input.state == PRESSED)
		return (RELEASED);
	return (REST);
}

int		update_inputs(t_input *inputs, t_env *env)
{
	size_t	i;

	i = 0;
	while (i < MAX_INPUTS)
	{
		inputs[i].state = update_input_state(inputs[i], env);
		i++;
	}
	return (0);
}

int		process_inputs(t_input *inputs, t_env *env)
{
	update_inputs(inputs, env);
	if (inputs[DRAW_MODE].state == RELEASED)
	{
		ft_printf("Draw mode swapped\n");
		env->polygon_mode = env->polygon_mode == GL_LINE ? GL_FILL : GL_LINE;
	}
	if (inputs[LEFT].state == PRESSED)
	{
		move_object(&env->objects[0].instances[0], new_v3(-0.01f, 0.0f, 0.0f));
	}
	if (inputs[RIGHT].state == PRESSED)
	{
		move_object(&env->objects[0].instances[0], new_v3(0.01f, 0.0f, 0.0f));
	}
	if (inputs[UP].state == PRESSED)
	{
		move_object(&env->objects[0].instances[0], new_v3(0.0f, 0.01f, 0.0f));
	}
	if (inputs[DOWN].state == PRESSED)
	{
		move_object(&env->objects[0].instances[0], new_v3(0.0f, -0.01f, 0.0f));
	}
	return (0);
}