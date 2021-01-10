/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fatal_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 16:39:01 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/10 16:39:02 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "scop.h"

void	ft_fatal_error(const char *str, t_env *env)
{
	ft_dprintf(STDERR_FILENO, "{red}[CRITICAL ERROR]\n", str);
	ft_dprintf(STDERR_FILENO, "%s\n{reset}", str);
	free_all(env);
	exit(EXIT_FAILURE);
}
