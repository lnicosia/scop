/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 16:39:21 by lnicosia          #+#    #+#             */
/*   Updated: 2021/09/10 10:47:50 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include "libft.h"
#include "inputs.h"
#include "light.h"

void	init_light(t_env *env)
{
	glUseProgram(env->shaders[0]);
	glUniform1i(glGetUniformLocation(env->shaders[0], env->diffuse_names[0]), 0);
	glUniform3fv(glGetUniformLocation(env->shaders[0], "camPos"), 1,
	(float*)&env->camera.pos);
	glUniform3fv(glGetUniformLocation(env->shaders[0], "light.pos"), 1,
	(float*)&env->objects[0].instances[0].transform.pos);
	set_ambient(env->shaders[0], new_v3(0.1f, 0.1f, 0.1f));
	set_diffuse(env->shaders[0], new_v3(0.5f, 0.5f, 0.5f));
	set_specular(env->shaders[0], new_v3(1.0f, 1.0f, 1.0f));
	env->light_mode = LIGHT_OFF;
}

int		scop(int ac, char **av)
{
	t_env		env;
	t_input		inputs[MAX_INPUTS];

	ft_bzero(&env, sizeof(env));
	if (init_opengl(&env))
		return (-1);
	init_inputs(inputs);
	env.selected_axe = SELECT_AXE_X;
	env.draw_skybox = NO;
	if (init_object("resources/objects/Cube/Cube.obj", &env))
		ft_fatal_error("", &env);
	add_object(0, &env);
	move_object(&env.objects[0].instances[0], new_v3(1.f, 0.75f, 0.f));
	scale_object(&env.objects[0].instances[0], new_v3(-0.85f, -0.85f, -0.85f));
	if (ac > 1)
	{
		if (init_object(av[1], &env))
			ft_fatal_error("", &env);
	}
	else
	{
		if (init_object("resources/objects/Cube/Cube.obj", &env))
			ft_fatal_error("", &env);
	}
	add_object(1, &env);
	env.instance_count++;
	move_object(&env.objects[1].instances[0], new_v3(0.f, -0.75f, 2.0f));
	init_shader("resources/shaders/default_shader.vs",
	"resources/shaders/default_shader.fs", &env);
	init_shader("resources/shaders/default_shader.vs",
	"resources/shaders/default_shader_no_light.fs", &env);
	init_shader("resources/shaders/light_shader.vs",
	"resources/shaders/light_shader.fs", &env);
	init_shader("resources/shaders/cubemap_shader.vs",
	"resources/shaders/cubemap_shader.fs", &env);
	init_light(&env);
	while (!glfwWindowShouldClose(env.window))
	{
		if (process_inputs(inputs, &env))
			ft_fatal_error("Error in inputs", &env);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (env.draw_skybox == YES)
			draw_skybox(env.cubemaps[0].id, env.shaders[3], &env);
		rotate_object(&env.objects[1].instances[0], new_v3(0.0f, 0.005f, 0.0f));
		for (unsigned int i = 0; i < env.instance_count; i++)
		{
			draw_object(&env.objects[1], i, env.shaders[env.light_mode], &env);
		}
		// Drawing the light
		draw_object(&env.objects[0], 0, env.shaders[2], &env);
		glfwSwapBuffers(env.window);
		glfwPollEvents();
	}
	free_all(&env);
	return (0);
}
