/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 19:20:44 by lnicosia          #+#    #+#             */
/*   Updated: 2021/09/06 18:02:20 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADER_H
# define SHADER_H

typedef struct			s_pipeline_shader
{
	unsigned int		id;
}						t_pipeline_shader;

typedef struct			s_shader
{
	char				*source_file;
	char				*name;
	t_pipeline_shader	vertex_shader;
	t_pipeline_shader	fragment_shader;
	unsigned int		id;
	int					state;
}						t_shader;

#endif
