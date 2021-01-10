/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 14:57:26 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/10 15:06:51 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H
# include "glad/glad.h"
# include <GLFW/glfw3.h>

/*
** Defines all the env structure that will contains everything globally needed
** by the program
*/

typedef struct	s_env
{
	GLFWwindow*	window;
}				t_env;

#endif
