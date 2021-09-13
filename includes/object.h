/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 21:15:17 by lnicosia          #+#    #+#             */
/*   Updated: 2021/09/13 10:38:16 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H
# include "libmft.h"
# include <stdlib.h>
# define MAX_OBJ_TEXT 8
# define MAX_ACTIVE_TEXTURES 4

enum				parsing_mode
{
	FULL,
	GENERATE_UV
};

typedef struct		s_vertex
{
	t_v3			pos;
	t_v3			norm;
	t_v2			text;
}					t_vertex;


typedef struct		s_transform
{
	t_v3			pos;
	t_v3			rotation;
	t_v3			scale;
}					t_transform;

typedef struct		s_instance
{
	size_t			id;
	unsigned int	textures[MAX_ACTIVE_TEXTURES];
	t_transform		transform;
	float			matrix[16];
	char			padding[4];
}					t_instance;

typedef struct		s_object
{
	const char		*name;
	t_vertex		*vertices;
	t_instance		*instances;
	unsigned int	*indices;
	size_t			id;
	size_t			count;
	t_v3			center;
	t_v3			range;
	unsigned int	size;
	unsigned int	vao;
	unsigned int	vbo;
	unsigned int	ebo;
	unsigned int	nb_indices;
	int				nb_textures;
	int				no_uv;
	unsigned int	nb_vertices;
}					t_object;

#endif
