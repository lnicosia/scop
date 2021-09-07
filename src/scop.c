/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 16:39:21 by lnicosia          #+#    #+#             */
/*   Updated: 2021/09/07 17:46:04 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include "env.h"
#include "libft.h"
#include "inputs.h"

int	scop(int ac, char **av)
{
	t_env		env;
	t_input		inputs[MAX_INPUTS];

	ft_bzero(&env, sizeof(env));
	if (init_opengl(&env))
		return (-1);
	init_inputs(inputs);
	env.selected_axe = SELECT_AXE_X;
	unsigned int textures[MAX_ACTIVE_TEXTURES];
    textures[0] = env.textures[1];
	unsigned int textures2[MAX_ACTIVE_TEXTURES];
    textures2[0] = env.textures[1];
    //textures[1] = env.textures[1];
	init_object("resources/objects/Cube/Cube.obj", textures2, 1, &env);
	add_object(0, &env);
	move_object(&env.objects[0].instances[0], new_v3(1.f, 0.75f, 0.f));
	scale_object(&env.objects[0].instances[0], new_v3(-0.85f, -0.85f, -0.85f));
	if (ac > 1)
		init_object(av[1], textures, 1, &env);
	else
		init_object("resources/objects/Cube/Cube.obj", textures, 1, &env);
	add_object(1, &env);
	env.instance_count++;
	move_object(&env.objects[1].instances[0], new_v3(0.f, -0.75f, 2.0f));
	init_shader("resources/shaders/default_shader.vs",
	"resources/shaders/default_shader.fs", &env);
	init_shader("resources/shaders/default_shader.vs",
	"resources/shaders/default_shader_no_light.fs", &env);
	init_shader("resources/shaders/light_shader.vs",
	"resources/shaders/light_shader.fs", &env);
	glUseProgram(env.shaders[0]);
	glUniform3fv(glGetUniformLocation(env.shaders[0], "camPos"), 1,
	(float*)&env.camera.pos);
	glUniform3fv(glGetUniformLocation(env.shaders[0], "light.pos"), 1,
	(float*)&env.objects[0].instances[0].transform.pos);
	glUniform3f(glGetUniformLocation(env.shaders[0], "light.ambient"),
	0.1f, 0.1f, 0.1f);
	glUniform3f(glGetUniformLocation(env.shaders[0], "light.diffuse"),
	0.5f, 0.5f, 0.5f);
	glUniform3f(glGetUniformLocation(env.shaders[0], "light.specular"),
	1.0f, 1.0f, 1.0f);
	glUniform3f(glGetUniformLocation(env.shaders[0], "material.ambient"),
	1.0f, 0.5f, 0.31f);
	glUniform3f(glGetUniformLocation(env.shaders[0], "material.diffuse"),
	1.0f, 0.5f, 0.31f);
	glUniform3f(glGetUniformLocation(env.shaders[0], "material.specular"),
	0.5f, 0.5f, 0.5f);
	glUniform1f(glGetUniformLocation(env.shaders[0], "material.shininess"),
	32.0f);
	while (!glfwWindowShouldClose(env.window))
	{
		if (process_inputs(inputs, &env))
			ft_fatal_error("Error in inputs", &env);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
