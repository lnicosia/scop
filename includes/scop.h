/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 17:56:35 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/10 16:43:37 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H
# include "env.h"
# include <GLFW/glfw3.h>

int		scop(int ac, char **av);
int		init_opengl(t_env *env);
void	free_all(t_env *env);
void	ft_fatal_error(const char *str, t_env *env);
void	viewport_update_callback(GLFWwindow *window, int width, int height);

#endif
