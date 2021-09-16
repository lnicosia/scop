/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubemap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 15:05:32 by lnicosia          #+#    #+#             */
/*   Updated: 2021/09/16 09:56:38 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBEMAP_H
# define CUBEMAP_H

typedef struct		s_cubemap
{
	const char		*name;
	unsigned int	texture;
	unsigned int	vao;
	unsigned int	vbo;
	char			padding[4];
}					t_cubemap;

void				print_cubemap(t_cubemap *cubemap);

#endif