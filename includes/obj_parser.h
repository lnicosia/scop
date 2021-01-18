/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 20:45:18 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/18 21:36:56 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_PARSER_H
# define OBJ_PARSER_H
# include "env.h"

typedef struct		s_obj_parser
{
	unsigned int	indices[4];
	char			*line;
	unsigned int	nb_vertices;
	unsigned int	nb_tex;
	unsigned int	nb_norm;
	unsigned int	count;
	int				i;
	char			padding[4];
}					t_obj_parser;


#endif