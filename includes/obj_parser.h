/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 20:45:18 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/19 13:33:17 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_PARSER_H
# define OBJ_PARSER_H
# include "env.h"

typedef struct		s_obj_parser
{
	t_v3			*pos;
	t_v3			*norm;
	t_v2			*tex;
	unsigned int	indices[4];
	unsigned int	*combinations;
	char			*line;
	unsigned int	nb_vertices;
	unsigned int	nb_tex;
	unsigned int	nb_norm;
	unsigned int	count;
	unsigned int	combination_size;
	unsigned int	nb_combinations;
	int				i;
	char			padding[4];
}					t_obj_parser;


#endif