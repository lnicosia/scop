/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 16:39:21 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/10 16:45:16 by lnicosia         ###   ########.fr       */
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
		glfwSwapBuffers(env.window);
		glfwPollEvents();
	}
	return (0);
}
