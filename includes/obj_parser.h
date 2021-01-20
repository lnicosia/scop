/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 20:45:18 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/20 22:45:03 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_PARSER_H
# define OBJ_PARSER_H
# include "env.h"

typedef struct		s_index
{
	unsigned int	pos;
	unsigned int	uv;
	unsigned int	norm;
}					t_index;

typedef struct		s_obj_parser
{
	t_v3			*pos;
	t_v3			*norm;
	t_v2			*tex;
	t_index			*face_indices;
	t_index			*unique_indices;
	char			*line;
	unsigned int	nb_vertices;
	unsigned int	nb_tex;
	unsigned int	nb_norm;
	unsigned int	nb_indices;
	unsigned int	count;
	unsigned int	nb_unique_indices;
	unsigned int	face_size;
	unsigned int	face_start;
	unsigned int	max_face_size;
	int				i;
	int				fd;
	char			padding[4];
}					t_obj_parser;


#endif