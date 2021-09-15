/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 12:58:23 by lnicosia          #+#    #+#             */
/*   Updated: 2021/09/15 16:23:20 by lnicosia         ###   ########.fr       */
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
	inputs[CURRENT_TEXTURE].key1 = GLFW_KEY_T;
	inputs[LIGHT_MODE].key1 = GLFW_KEY_L;
	inputs[ADD_OBJECT].key1 = GLFW_KEY_KP_ADD;
	inputs[SELECT_OBJECT_0].key1 = GLFW_KEY_0;
	inputs[SELECT_OBJECT_0].key2 = GLFW_KEY_KP_0;
	inputs[SELECT_OBJECT_1].key1 = GLFW_KEY_1;
	inputs[SELECT_OBJECT_1].key2 = GLFW_KEY_KP_1;
	inputs[SELECT_OBJECT_2].key1 = GLFW_KEY_2;
	inputs[SELECT_OBJECT_2].key2 = GLFW_KEY_KP_2;
	inputs[SELECT_OBJECT_3].key1 = GLFW_KEY_3;
	inputs[SELECT_OBJECT_3].key2 = GLFW_KEY_KP_3;
	inputs[SELECT_OBJECT_4].key1 = GLFW_KEY_4;
	inputs[SELECT_OBJECT_4].key2 = GLFW_KEY_KP_4;
	inputs[SELECT_OBJECT_5].key1 = GLFW_KEY_5;
	inputs[SELECT_OBJECT_5].key2 = GLFW_KEY_KP_5;
	inputs[SELECT_OBJECT_6].key1 = GLFW_KEY_6;
	inputs[SELECT_OBJECT_6].key2 = GLFW_KEY_KP_6;
	inputs[SELECT_OBJECT_7].key1 = GLFW_KEY_7;
	inputs[SELECT_OBJECT_7].key2 = GLFW_KEY_KP_7;
	inputs[SELECT_OBJECT_8].key1 = GLFW_KEY_8;
	inputs[SELECT_OBJECT_8].key2 = GLFW_KEY_KP_8;
	inputs[SELECT_OBJECT_9].key1 = GLFW_KEY_9;
	inputs[SELECT_OBJECT_9].key2 = GLFW_KEY_KP_9;
	inputs[SELECT_AXE_X].key1 = GLFW_KEY_F1;
	inputs[SELECT_AXE_Y].key1 = GLFW_KEY_F2;
	inputs[SELECT_AXE_Z].key1 = GLFW_KEY_F3;
	inputs[PAGE_UP].key1 = GLFW_KEY_PAGE_UP;
	inputs[PAGE_DOWN].key1 = GLFW_KEY_PAGE_DOWN;
	inputs[SHIFT_MOD].key1 = GLFW_KEY_LEFT_SHIFT;
	inputs[SHIFT_MOD].key2 = GLFW_KEY_RIGHT_SHIFT;
	inputs[DRAW_SKYBOX].key1 = GLFW_KEY_C;
	inputs[TEXTURE_MODE].key1 = GLFW_KEY_N;
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
		look_at(env->look_at_matrix, env->camera.pos,
		env->camera.front, env->camera.up);
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
		direction.x = cosf(to_radians(env->camera.yaw));
		direction.y = sinf(to_radians(env->camera.pitch));
		direction.z = sinf(to_radians(env->camera.yaw));
		//env->camera.front = normalize(env->camera.front);
		env->camera.front = normalize(direction);
		env->mouse_x_start = x;
		env->mouse_y_start = y;
		look_at(env->look_at_matrix, env->camera.pos,
		env->camera.front, env->camera.up);
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
		switch (env->polygon_mode)
		{
			case GL_LINE:
				env->polygon_mode = GL_POINT;
				break;
			case GL_FILL:
				env->polygon_mode = GL_LINE;
				break;
			case GL_POINT:
				env->polygon_mode = GL_FILL;
				break;
		}
	}
	if (inputs[DRAW_SKYBOX].state == PRESS)
	{
		env->draw_skybox = env->draw_skybox == YES ? NO : YES;
	}
	if (inputs[LIGHT_MODE].state == PRESS)
	{
		env->light_mode = env->light_mode == LIGHT_ON ? LIGHT_OFF : LIGHT_ON;
	}
	if (inputs[CURRENT_TEXTURE].state == PRESS)
	{
		if (inputs[SHIFT_MOD].state == PRESSED)
		{
			if (env->current_text == 0)
				env->current_text = USABLE_TEXTURES;
			env->current_text--;
		}
		else
		{
			env->current_text++;
			if (env->current_text >= USABLE_TEXTURES)
				env->current_text = 0;
		}
		for (unsigned int i = 0; i < env->objects[1].nb_meshes; i++)
		{
			set_mesh_texture(&env->objects[1].meshes[i], env->selected_object, 0,
			env->textures[env->current_text]);
		}
	}
	if (inputs[TEXTURE_MODE].state == PRESS)
	{
		env->texture_mode = env->texture_mode == SINGLE_TEXTURE ? MULTIPLE_TEXTURES : SINGLE_TEXTURE;
		if (env->texture_mode == MULTIPLE_TEXTURES)
		{
			set_textures(env);
		}
		else
		{
			for (unsigned int i = 0; i < env->objects[1].nb_meshes; i++)
			{
				set_mesh_texture(&env->objects[1].meshes[i], env->selected_object, 0,
				env->textures[env->current_text]);
			}
		}
	}
	if (inputs[LEFT].state == PRESSED)
	{
		env->camera.pos = add_vec(env->camera.pos,
		mult_vec(normalize(cross_product(env->camera.front, env->camera.up)),
		env->camera.speed));
		look_at(env->look_at_matrix, env->camera.pos,
		env->camera.front, env->camera.up);
	}
	if (inputs[RIGHT].state == PRESSED)
	{
		env->camera.pos = sub_vec(env->camera.pos,
		mult_vec(normalize(cross_product(env->camera.front, env->camera.up)),
		env->camera.speed));
		look_at(env->look_at_matrix, env->camera.pos,
		env->camera.front, env->camera.up);
	}
	if (inputs[UP].state == PRESSED)
	{

		env->camera.pos = sub_vec(env->camera.pos,
		mult_vec(env->camera.front, env->camera.speed));
		look_at(env->look_at_matrix, env->camera.pos,
		env->camera.front, env->camera.up);
	}
	if (inputs[DOWN].state == PRESSED)
	{
		env->camera.pos = add_vec(env->camera.pos,
		mult_vec(env->camera.front, env->camera.speed));
		look_at(env->look_at_matrix, env->camera.pos,
		env->camera.front, env->camera.up);
	}
	if (inputs[ADD_OBJECT].state == PRESS && env->instance_count < 9)
	{
		add_object(1, env);
		env->instance_count++;
	}
	if (inputs[SELECT_OBJECT_1].state == PRESSED)
		env->selected_object = 0;
	if (inputs[SELECT_OBJECT_2].state == PRESSED && env->instance_count > 1)
		env->selected_object = 1;
	if (inputs[SELECT_OBJECT_3].state == PRESSED && env->instance_count > 2)
		env->selected_object = 2;
	if (inputs[SELECT_OBJECT_4].state == PRESSED && env->instance_count > 3)
		env->selected_object = 3;
	if (inputs[SELECT_OBJECT_5].state == PRESSED && env->instance_count > 4)
		env->selected_object = 4;
	if (inputs[SELECT_OBJECT_6].state == PRESSED && env->instance_count > 5)
		env->selected_object = 5;
	if (inputs[SELECT_OBJECT_7].state == PRESSED && env->instance_count > 6)
		env->selected_object = 6;
	if (inputs[SELECT_OBJECT_8].state == PRESSED && env->instance_count > 7)
		env->selected_object = 7;
	if (inputs[SELECT_OBJECT_9].state == PRESSED && env->instance_count > 8)
		env->selected_object = 8;
	if (inputs[SELECT_AXE_X].state == PRESS)
		env->selected_axe = SELECT_AXE_X;
	if (inputs[SELECT_AXE_Y].state == PRESS)
		env->selected_axe = SELECT_AXE_Y;
	if (inputs[SELECT_AXE_Z].state == PRESS)
		env->selected_axe = SELECT_AXE_Z;
	t_v3	move = {0.0f, 0.0f, 0.0f};
	switch (env->selected_axe)
	{
		case (SELECT_AXE_X):
			move.x = 0.05f;
			break;
		case (SELECT_AXE_Y):
			move.y = 0.05f;
			break;
		case (SELECT_AXE_Z):
			move.z = 0.05f;
			break;
	}
	if (inputs[PAGE_UP].state == PRESSED)
	{
		move_object(&env->objects[1].instances[env->selected_object], move);
	}
	if (inputs[PAGE_DOWN].state == PRESSED)
	{
		move_object(&env->objects[1].instances[env->selected_object], mult_vec(move, -1));
	}
	if (inputs[RESET].state == PRESSED)
	{
		init_camera(env);
	}
	return (0);
}
