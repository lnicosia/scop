/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 16:39:21 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/17 20:45:38 by lnicosia         ###   ########.fr       */
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
