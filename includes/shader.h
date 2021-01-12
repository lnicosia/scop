/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 19:20:44 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/12 23:13:41 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADER_H
# define SHADER_H
#include "env.h"

typedef struct			s_pipeline_shader
{
	unsigned int		id;
}						t_pipeline_shader;

typedef struct			s_shader
{
	char				*source_file;
	t_pipeline_shader	vertex_shader;
	t_pipeline_shader	fragment_shader;
	unsigned int		id;
	int					state;
}						t_shader;

char					*read_shader(const char *file);
int						init_pipeline_shader(GLenum type, const char *file,
t_env *env);
int						init_program(unsigned int vertex_shader,
unsigned int fragment_shader, t_env *env);

#endif
