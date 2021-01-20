/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 23:48:08 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/20 00:49:08 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft.h"
#include "scop.h"
#include "obj_parser.h"

int		set_new_index(unsigned int i, t_index index, t_obj_parser *parser,
t_object *object)
{
	unsigned int	j;

	j = 0;
	while (j < parser->nb_indices)
	{
		if (parser->indices[j].pos == index.pos
			&& parser->indices[j].uv == index.uv
			&& parser->indices[j].norm == index.norm)
		{
			object->indices[object->nb_indices] = j;
			return (0);
		}
		j++;
	}
	if (!(object->vertices = (t_vertex*)realloc(object->vertices, 
		sizeof(t_vertex) * (object->nb_vertices + 1))))
		return (ft_perror("Failed to init new object vertices"));
	object->vertices[object->nb_vertices].pos =
	parser->pos[index.pos - 1];
	object->vertices[object->nb_vertices++].text =
	parser->tex[index.uv - 1];
	if (!(object->indices = (unsigned int*)realloc(object->indices,
		(unsigned int)sizeof(unsigned int) * (object->nb_indices + 3))))
		return(custom_error("Failed to realloc vertices"));
	object->indices[object->nb_indices + i] = object->nb_indices + i;
	object->nb_indices++;
	ft_printf("Index %d/%d/%d added \n", index.pos, index.uv, index.norm);
	if (!(parser->indices = (t_index*)realloc(parser->indices,
		sizeof(t_index) * ++parser->nb_indices)))
		return (ft_perror("Failed to realloc parser indices\n"));
	parser->indices[parser->nb_indices - 1] = index;
	return (0);
}

int		parse_current_index(unsigned int i, t_obj_parser *parser,
t_object *object)
{
	t_index	index;

	ft_bzero(&index, sizeof(index));
	if (!*parser->line || valid_int(parser->line))
		return (custom_error("Invalid vertex pos\n"));
	index.pos = (unsigned int)ft_atoi(parser->line);
	parser->line = skip_number(parser->line);
	if (!*parser->line || *parser->line == ' ' || *parser->line == '\r')
		return (set_new_index(i, index, parser, object));
	if (*parser->line != '/')
		return (custom_error("Expected / in indices declaration\n"));
	parser->line++;
	if (!*parser->line || valid_int(parser->line))
		return (custom_error("Invalid vertex pos\n"));
	index.uv = (unsigned int)ft_atoi(parser->line);
	parser->line = skip_number(parser->line);
	if (!*parser->line || *parser->line == ' ' || *parser->line == '\r')
		return (set_new_index(i, index, parser, object));
	if (*parser->line != '/')
		return (custom_error("Expected / in indices declaration\n"));
	parser->line++;
	if (!*parser->line || valid_int(parser->line))
		return (custom_error("Invalid vertex pos\n"));
	index.norm = (unsigned int)ft_atoi(parser->line);
	parser->line = skip_number(parser->line);
	return (set_new_index(i, index, parser, object));
}

int		parse_index(t_obj_parser *parser, t_object *object, t_env *env)
{
	unsigned int	i;

	i = 0;
	(void)env;
	parser->line++;
	if (!*parser->line)
		return (-1);
	parser->line = skip_spaces(parser->line);
	while (*parser->line)
	{
		if (parse_current_index(i, parser, object))
			return (-1);
		if (*parser->line)
			parser->line++;
		i++;
	}
	ft_printf("Current face added\n");
	return (0);
}

int		parse_normal(t_obj_parser *parser, t_object *object, t_env *env)
{
	t_v3	normal;

	(void)object;
	ft_printf("NORMAL: ");
	parser->line++;
	if (!*parser->line)
		return (-1);
	parser->line = skip_spaces(parser->line);
	if (!*parser->line || valid_double(parser->line))
		return (-1);
	normal.x = (float)ft_atof(parser->line);
	ft_printf("x = %f", normal.x);
	parser->line = skip_number(parser->line);
	parser->line = skip_spaces(parser->line);
	if (!*parser->line || valid_double(parser->line))
		return (-1);
	normal.y = (float)ft_atof(parser->line);
	ft_printf(" y = %f", normal.y);
	parser->line = skip_number(parser->line);
	parser->line = skip_spaces(parser->line);
	if (!*parser->line || valid_double(parser->line))
		return (-1);
	normal.z = (float)ft_atof(parser->line);
	ft_printf(" z = %f\n", normal.z);
	if (!(parser->norm = (t_v3*)realloc(parser->norm,
		(unsigned int)sizeof(t_v3) * ++parser->nb_norm)))
		ft_fatal_error("Failed to realloc vertices", env);
	parser->norm[parser->nb_norm - 1] = normal;
	return (0);
}

int		parse_uv(t_obj_parser *parser, t_object *object, t_env *env)
{
	t_v2	tex;

	ft_printf("TEXTURE ");
	(void)object;
	parser->line++;
	if (!*parser->line)
		return (-1);
	parser->line = skip_spaces(parser->line);
	if (!*parser->line || valid_double(parser->line))
		return (-1);
	tex.x = (float)ft_atof(parser->line);
	ft_printf("x = %f", tex.x);
	parser->line = skip_number(parser->line);
	parser->line = skip_spaces(parser->line);
	if (!*parser->line || valid_double(parser->line))
		return (-1);
	tex.y = (float)ft_atof(parser->line);
	ft_printf(" y = %f\n", tex.y);
	if (!(parser->tex = (t_v2*)realloc(parser->tex,
		(unsigned int)sizeof(t_v2) * ++parser->nb_tex)))
		ft_fatal_error("Failed to realloc vertices", env);
	parser->tex[parser->nb_tex - 1] = tex;
	return (0);
}

int		parse_vertex(t_obj_parser *parser, t_object *object, t_env *env)
{
	t_v3	vertex;

	(void)object;
	ft_printf("VERTEX ");
	if (!*parser->line)
		return (-1);
	parser->line = skip_spaces(parser->line);
	if (!*parser->line || valid_double(parser->line))
		return (-1);
	vertex.x = (float)ft_atof(parser->line);
	ft_printf("x = %f", vertex.x);
	parser->line = skip_number(parser->line);
	parser->line = skip_spaces(parser->line);
	if (!*parser->line || valid_double(parser->line))
		return (-1);
	vertex.y = (float)ft_atof(parser->line);
	ft_printf(" y = %f", vertex.y);
	parser->line = skip_number(parser->line);
	parser->line = skip_spaces(parser->line);
	if (!*parser->line || valid_double(parser->line))
		return (-1);
	vertex.z = (float)ft_atof(parser->line);
	ft_printf(" z = %f\n", vertex.z);
	if (!(parser->pos = (t_v3*)realloc(parser->pos,
		(unsigned int)sizeof(t_v3) * ++parser->nb_vertices)))
		ft_fatal_error("Failed to realloc vertices", env);
	parser->pos[parser->nb_vertices - 1] = vertex;
	return (0);
}

int		parse_object_line(t_obj_parser *parser, t_object *object, t_env *env)
{
	if (!*parser->line)
		return (custom_error("Empty line!\n"));
	if (*parser->line == 'v')
	{
		if (!*(++parser->line))
			return (custom_error("Empty vertex or multiple spaces!\n"));
		if (*parser->line == ' ' && parse_vertex(parser, object, env))
			return (custom_error("Error while parsing vertices\n"));
		else if (*parser->line == 't' && parse_uv(parser, object, env))
			return (custom_error("Error while parsing uv's\n"));
		else if (*parser->line == 'n' && parse_normal(parser, object, env))
			return (custom_error("Error while parsing normals\n"));
	}
	else if (*parser->line == 'f')
	{
		if (parse_index(parser, object, env))
			return (custom_error("Error while parsing index\n"));
	}
	return (0);
}

void	free_obj_parser(t_obj_parser *parser)
{
	ft_memdel((void**)&parser->pos);
	ft_memdel((void**)&parser->tex);
	ft_memdel((void**)&parser->norm);
	ft_memdel((void**)&parser->indices);
}

int		init_object_from_parser(t_obj_parser *parser, t_object *object,
t_env *env)
{
	/*unsigned int	i;

	i = 0;
	if (!(object->vertices = (t_vertex*)ft_memalloc(
		sizeof(t_vertex) * parser->nb_indices)))
		return (ft_perror("Failed to init new object vertices"));
	ft_printf("Found %d indices\n", parser->nb_indices);
	object->nb_vertices = parser->nb_indices;
	while (i < parser->nb_indices)
	{
		ft_printf("i = %d\n", i);
		object->vertices[i].pos = parser->pos[parser->indices[i].pos - 1];
		object->vertices[i].text = parser->tex[parser->indices[i].pos - 1];
		ft_printf("Adding vertex %d: {%f, %f, %f,  %f, %f}\n",
		parser->indices[i].pos,
		object->vertices[i].pos.x, object->vertices[i].pos.y,
		object->vertices[i].pos.z, object->vertices[i].text.x,
		object->vertices[i].text.y);
		i++;
	}*/
	/*i = 0;
	while (i < object->nb_indices)
	{
		object->indices[i] = i - 1;
		i++;
	}*/
	(void)parser;
	(void)object;
	(void)env;
	return (0);
}

int		parse_object(const char *source_file, t_object *object, t_env *env)
{
	int				fd;
	int				ret;
	char			*tmp;
	t_obj_parser	parser;

	ret = 0;
	ft_bzero(&parser, sizeof(parser));
	if ((fd = open(source_file, O_RDONLY)) < 0)
		return (custom_error("Could not open \"%s\"\n", source_file));
	while ((ret = get_next_line(fd, &parser.line)))
	{
		ft_printf("Reading %s\n", parser.line);
		tmp = parser.line;
		if (parse_object_line(&parser, object, env))
		{
			free_obj_parser(&parser);
			ft_strdel(&tmp);
			return (custom_error("Parsing error in \"%s\"\n", source_file));
		}
		ft_strdel(&tmp);
	}
	if (init_object_from_parser(&parser, object, env))
	{
		free_obj_parser(&parser);
		return (-1);
	}
	free_obj_parser(&parser);
	return (0);
}
