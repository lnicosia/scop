/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 16:39:21 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/20 22:11:27 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include "env.h"
#include "libft.h"

int	scop(int ac, char **av)
{
	t_env	env;

	(void)ac;
	(void)av;
	ft_bzero(&env, sizeof(env));
	if (init_opengl(&env))
		return (-1);
	unsigned int *textures = (unsigned int*)ft_memalloc(sizeof(unsigned int) * 2);
    textures[0] = env.textures[0];
    textures[1] = env.textures[1];
	init_object(av[1], textures, 2, &env);
	init_shader("resources/shaders/default_shader.vs",
	"resources/shaders/default_shader.fs", &env);
	add_object(0, &env);
	scale_object(&env.objects[0].instances[0], new_v3(-0.75f, -0.75f, -0.75f));
	//move_object(&env->objects[0].instances[0], new_v3(0.25f, 0.0f, 0.0f));
	//rotate_object(&env->objects[0].instances[0], new_v3(0.0f, to_radians(20.0f), 0.0f));

	while (!glfwWindowShouldClose(env.window))
	{
		glClearColor(0.4f, 0.4f, 0.6f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		draw_triangle(&env);
		glfwSwapBuffers(env.window);
		glfwPollEvents();
	}
	free_all(&env);
	return (0);
}
