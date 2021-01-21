/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 12:58:23 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/21 14:01:50 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include "inputs.h"

int		init_inputs(t_input *inputs)
{
	size_t	i;

	i = 0;
	while (i < MAX_INPUTS)
	{
		inputs[i].key1 = -1;
		inputs[i].key2 = -1;
		inputs[i].state = UP;
		i++;
	}	
	inputs[DRAW_MODE].key1 = GLFW_KEY_M;
	inputs[DRAW_MODE].key2 = -1;
	inputs[ESCAPE].key1 = GLFW_KEY_ESCAPE;
	return (0);
}

enum e_input_states		update_input_state(t_input input, t_env *env)
{
	if ((input.key1 != -1 &&
		glfwGetKey(env->window, input.key1) == GLFW_PRESS)
		|| (input.key2 != -1
		&& glfwGetKey(env->window, input.key2) == GLFW_PRESS))
		return (PRESSED);
	if (input.state == PRESSED)
		return (RELEASED);
	return (UP);
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
	return (0);
}