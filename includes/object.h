/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 21:15:17 by lnicosia          #+#    #+#             */
/*   Updated: 2021/09/13 10:38:16 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef mesh_H
# define mesh_H
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
	unsigned int	texture_mode;
	unsigned int	current_text;
	char			padding[4];
}					t_instance;

typedef struct		s_material
{
	unsigned int	textures[MAX_ACTIVE_TEXTURES];
	unsigned int	shader;
}					t_material;

typedef struct		s_mesh
{
	const char		*name;
	t_vertex		*vertices;
	unsigned int	*indices;
	t_material		*instances;
	size_t			id;
	size_t			nb_textures;
	t_v3			center;
	t_v3			range;
	unsigned int	size;
	unsigned int	vao;
	unsigned int	vbo;
	unsigned int	ebo;
	unsigned int	nb_indices;
	unsigned int	nb_vertices;
	int				no_uv;
	char			padding[4];
}					t_mesh;

typedef struct		s_object
{
	t_mesh			*meshes;
	t_instance		*instances;
	const char		*name;
	size_t			count;
	size_t			id;
	t_v3			center;
	t_v3			range;
	unsigned int	nb_meshes;
	unsigned int	nb_vertices;
	//char			padding[4];
}					t_object;


#endif
