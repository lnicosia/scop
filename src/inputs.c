/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 12:58:23 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/24 17:01:24 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include "libft.h"
#include "inputs.h"
#include <math.h>

int				init_inputs(t_input *inputs)
{
	size_t	i;

	i = 0;
	while (i < MAX_INPUTS)
	{
		inputs[i].key1 = GLFW_KEY_UNKNOWN;
		inputs[i].key2 = GLFW_KEY_UNKNOWN;
		inputs[i].state = RELEASED;
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
	inputs[MOUSE_LEFT].key1 = GLFW_MOUSE_BUTTON_LEFT;
	inputs[MOUSE_LEFT].key2 = GLFW_MOUSE_BUTTON_LEFT;
	inputs[MOUSE_RIGHT].key1 = GLFW_MOUSE_BUTTON_RIGHT;
	inputs[MOUSE_RIGHT].key2 = GLFW_MOUSE_BUTTON_RIGHT;
	inputs[RESET].key1 = GLFW_KEY_R;
	return (0);
}

t_input_states	update_input_state(t_input input,
int (*function)(GLFWwindow*, int), t_env *env)
{
	if ((input.key1 != GLFW_KEY_UNKNOWN &&
		function(env->window, input.key1) == GLFW_PRESS)
		|| (input.key2 != GLFW_KEY_UNKNOWN
		&& function(env->window, input.key2) == GLFW_PRESS))
		{
			if (input.state == RELEASED)
				return (PRESS);
			return (PRESSED);
		}
	if (input.state == PRESSED)
		return (RELEASE);
	return (RELEASED);
}

int				update_inputs(t_input *inputs, t_env *env)
{
	size_t	i;

	inputs[MOUSE_LEFT].state = update_input_state(inputs[MOUSE_LEFT],
	glfwGetMouseButton, env);
	inputs[MOUSE_RIGHT].state = update_input_state(inputs[MOUSE_RIGHT],
	glfwGetMouseButton, env);
	i = ESCAPE;
	while (i < MAX_INPUTS)
	{
		inputs[i].state = update_input_state(inputs[i], glfwGetKey, env);
		i++;
	}
	return (0);
}

int				process_mouse(t_input *inputs, t_env *env)
{
	double	x;
	double	y;
	t_v3	direction;

	glfwGetCursorPos(env->window, &x, &y);
	if (inputs[MOUSE_RIGHT].state == PRESS)
	{
		env->mouse_x_start = x;
		env->mouse_y_start = y;
		glfwSetInputMode(env->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	if (inputs[MOUSE_RIGHT].state == PRESSED)
	{
		env->camera.pos.z += (float)(env->mouse_y_start - y) / 500.0f;
		env->camera.pos.x += (float)(env->mouse_x_start - x) / 500.0f;
		env->mouse_x_start = x;
		env->mouse_y_start = y;
	}
	if (inputs[MOUSE_RIGHT].state == RELEASE)
	{
		glfwSetInputMode(env->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	if (inputs[MOUSE_LEFT].state == PRESS)
	{
		env->mouse_x_start = x;
		env->mouse_y_start = y;
		glfwSetInputMode(env->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	if (inputs[MOUSE_LEFT].state == PRESSED)
	{
		//env->camera.front.y -= (float)(env->mouse_y_start - y) / 500.0f;
		//env->camera.front.x -= (float)(env->mouse_x_start - x) / 500.0f;
		env->camera.yaw -= (float)(env->mouse_x_start - x) * env->sensi;
		env->camera.pitch -= (float)(env->mouse_y_start - y) * env->sensi;
		if (env->camera.pitch > 89.0f)
			env->camera.pitch = 89.0f;
		if (env->camera.pitch < -89.0f)
			env->camera.pitch = -89.0f;
		direction.x = cosf(to_radians(env->camera.yaw)
		* cosf(to_radians(env->camera.pitch)));
		direction.y = sinf(to_radians(env->camera.pitch));
		direction.z = sinf(to_radians(env->camera.yaw))
		* cosf(to_radians(env->camera.pitch));
		(void)direction;
		//env->camera.front = normalize(env->camera.front);
		env->camera.front = normalize(direction);
		env->mouse_x_start = x;
		env->mouse_y_start = y;
	}
	if (inputs[MOUSE_LEFT].state == RELEASE)
	{
		glfwSetInputMode(env->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	return (0);
}

int				process_inputs(t_input *inputs, t_env *env)
{
	env->camera.speed = 1.5f * ((float)glfwGetTime() - env->last_frame);
	env->last_frame = (float)glfwGetTime();
	update_inputs(inputs, env);
	process_mouse(inputs, env);
	if (inputs[DRAW_MODE].state == PRESS)
	{
		ft_printf("Draw mode swapped\n");
		env->polygon_mode = env->polygon_mode == GL_LINE ? GL_FILL : GL_LINE;
	}
	if (inputs[LEFT].state == PRESSED)
	{
		env->camera.pos = add_vec(env->camera.pos,
			mult_vec(normalize(cross_product(env->camera.front, env->camera.up)),
			env->camera.speed));
	}
	if (inputs[RIGHT].state == PRESSED)
	{
		env->camera.pos = sub_vec(env->camera.pos,
			mult_vec(normalize(cross_product(env->camera.front, env->camera.up)),
			env->camera.speed));
	}
	if (inputs[UP].state == PRESSED)
	{
		env->camera.pos = sub_vec(env->camera.pos,
		mult_vec(env->camera.front, env->camera.speed));
	}
	if (inputs[DOWN].state == PRESSED)
	{
		env->camera.pos = add_vec(env->camera.pos,
		mult_vec(env->camera.front, env->camera.speed));
	}
	if (inputs[RESET].state == PRESSED)
	{
		init_camera(env);
	}
	return (0);
}
