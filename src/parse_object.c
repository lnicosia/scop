/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 23:48:08 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/18 22:04:34 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft.h"
#include "scop.h"
#include "obj_parser.h"

int		parse_normal_index(t_obj_parser *parser, t_object *object,
t_env *env)
{
	parser->line++;
	parser->line = skip_number(parser->line);
	(void)parser;
	(void)object;
	(void)env;
	return (0);
}

int		parse_uv_index(t_obj_parser *parser, t_object *object,
t_env *env)
{
	parser->line++;
	parser->line = skip_number(parser->line);
	(void)parser;
	(void)object;
	(void)env;
	return (0);
}

int		parse_current_index(t_obj_parser *parser, t_object *object,
t_env *env)
{
	int		nb;

	if (!*parser->line || valid_int(parser->line))
			return (-1);
	nb = ft_atoi(parser->line);
	if (nb < 0 || nb > (int)object->nb_vertices)
		return (custom_error("\nIndex %d is invalid\n",
			parser->indices[parser->i]));
	parser->indices[parser->i] = (unsigned int)nb - 1;
	parser->line = skip_number(parser->line);
	if (*parser->line == '/' && parse_uv_index(parser, object, env))
		return (-1);
	if (*parser->line == '/' && parse_normal_index(parser, object, env))
		return (-1);
	parser->line = skip_spaces(parser->line);
	return (0);
}

int		parse_index(t_obj_parser *parser, t_object *object, t_env *env)
{
	(void)env;
	parser->line++;
	if (!*parser->line)
		return (-1);
	parser->line = skip_spaces(parser->line);
	parser->i = 0;
	ft_printf("Indices = ");
	while (parser->i < 3)
	{
		if (parse_current_index(parser, object, env))
			return (-1);
			ft_printf("%d ", parser->indices[parser->i]);
		parser->i++;
	}
	ft_printf("\n");
	if (!(object->indices = (unsigned int*)realloc(object->indices,
		(unsigned int)sizeof(unsigned int) * (object->nb_indices + 3))))
		ft_fatal_error("Failed to realloc vertices", env);
	object->indices[parser->count++] = parser->indices[0];
	object->indices[parser->count++] = parser->indices[1];
	object->indices[parser->count++] = parser->indices[2];
	object->nb_indices += 3;
	return (0);
}

int		parse_normal(t_obj_parser *parser, t_object *object, t_env *env)
{
	(void)object;
	(void)parser;
	(void)env;
	return (0);
}

int		parse_uv(t_obj_parser *parser, t_object *object, t_env *env)
{
	t_v2	tex;

	ft_printf("TEXTURE ");
	parser->line++;
	if (parser->nb_norm >= parser->nb_vertices)
		return (custom_error("Too much texture coordinates\n"));
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
	object->vertices[parser->nb_tex++].text = tex;
	(void)env;
	return (0);
}

int		parse_vertex(t_obj_parser *parser, t_object *object, t_env *env)
{
	t_v3	vertex;

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
	if (!(object->vertices = (t_vertex*)realloc(object->vertices,
		(unsigned int)sizeof(t_vertex) * ++object->nb_vertices)))
		ft_fatal_error("Failed to realloc vertices", env);
	object->vertices[object->nb_vertices - 1].pos = vertex;
	parser->nb_vertices++;
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
			return (custom_error("Error while parsing vertex\n"));
		else if (*parser->line == 't' && parse_uv(parser, object, env))
			return (custom_error("Error while parsing vertex\n"));
		else if (*parser->line == 'n' && parse_normal(parser, object, env))
			return (custom_error("Error while parsing vertex\n"));
	}
	else if (*parser->line == 'f')
	{
		if (parse_index(parser, object, env))
			return (custom_error("Error while parsing index\n"));
	}
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
		tmp = parser.line;
		if (parse_object_line(&parser, object, env))
			return (custom_error("Parsing error in \"%s\"\n", source_file));
		ft_strdel(&tmp);
	}
	return (0);
}