/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 16:39:21 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/22 09:03:41 by lnicosia         ###   ########.fr       */
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

	(void)ac;
	(void)av;
	ft_bzero(&env, sizeof(env));
	if (init_opengl(&env))
		return (-1);
	init_inputs(inputs);
	unsigned int *textures = (unsigned int*)ft_memalloc(sizeof(unsigned int) * 1);
    textures[0] = env.textures[1];
    //textures[1] = env.textures[1];
	init_object(av[1], textures, 1, &env);
	init_shader("resources/shaders/default_shader.vs",
	"resources/shaders/default_shader.fs", &env);
	add_object(0, &env);
	scale_object(&env.objects[0].instances[0], new_v3(-0.75f, -0.75f, -0.75f));
	/*add_object(0, &env);
	add_object(0, &env);
	scale_object(&env.objects[0].instances[1], new_v3(-0.75f, -0.75f, -0.75f));
	scale_object(&env.objects[0].instances[2], new_v3(-0.9f, -0.9f, -0.9f));
	move_object(&env.objects[0].instances[1], new_v3(-0.5f, 0.0f, 0.0f));
	move_object(&env.objects[0].instances[2], new_v3(-0.0f, 0.0f, -0.5f));*/
	while (!glfwWindowShouldClose(env.window))
	{
		if (process_inputs(inputs, &env))
			ft_fatal_error("Error in inputs", &env);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		draw_triangle(&env);
		glfwSwapBuffers(env.window);
		glfwPollEvents();
	}
	free_all(&env);
	return (0);
}
