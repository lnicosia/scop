/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 23:48:08 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/25 20:50:58 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft.h"
#include "scop.h"
#include "obj_parser.h"

int		scale_new_object(t_object *object)
{
	t_v3			min;
	t_v3			max;
	unsigned int	i;
	float			scale;

	min = object->vertices[0].pos;
	max = object->vertices[0].pos;
	i = 0;
	while (i < object->nb_vertices)
	{
		if (object->vertices[i].pos.x < min.x)
			min.x = object->vertices[i].pos.x;
		if (object->vertices[i].pos.x > max.x)
			max.x = object->vertices[i].pos.x;
		if (object->vertices[i].pos.y < min.y)
			min.y = object->vertices[i].pos.y;
		if (object->vertices[i].pos.y > max.y)
			max.y = object->vertices[i].pos.y;	
		if (object->vertices[i].pos.z < min.z)
			min.z = object->vertices[i].pos.z;
		if (object->vertices[i].pos.z > max.z)
			max.z = object->vertices[i].pos.z;	
		i++;
	}
	object->range.x = max.x - min.x;
	object->range.y = max.y - min.y;
	object->range.z = max.z - min.z;
	scale = (float)ft_fmax(object->range.x, object->range.y);
	scale = (float)ft_fmax(scale, object->range.z);
	i = 0;
	while (i < object->nb_vertices)
	{
		object->vertices[i].pos.x -= object->range.x / 2.0f + min.x;
		object->vertices[i].pos.y -= object->range.y / 2.0f + min.y;
		object->vertices[i].pos.z -= object->range.z / 2.0f + min.z;

		object->vertices[i].pos.x /= scale;
		object->vertices[i].pos.y /= scale;
		object->vertices[i].pos.z /= scale;
		i++;
	}
	return (0);
}

int		set_new_index(t_index index, t_obj_parser *parser)
{
	if (parser->face_size >= parser->max_face_size)
	{
		if (!(parser->face_indices = (t_index*)realloc(
			parser->face_indices, sizeof(t_index) * ++parser->max_face_size)))
			return (ft_perror("Failed to realloc parser indices\n"));
	}
	//ft_printf("Reading index %d/%d/%d\n", index.pos, index.uv, index.norm);
	parser->face_indices[parser->face_size] = index;
	parser->face_size++;
	return (0);
}

int		parse_current_index(t_obj_parser *parser)
{
	t_index	index;

	ft_bzero(&index, sizeof(index));
	//ft_printf("Line = %d\n", *parser->line, *parser->line);
	if (!*parser->line || valid_int(parser->line))
		return (custom_error("Invalid vertex pos\n"));
	index.pos = (unsigned int)ft_atoi(parser->line);
	parser->line = skip_number(parser->line);
	if (!*parser->line || *parser->line == ' ' || *parser->line == '\r')
		return (set_new_index(index, parser));
	if (*parser->line != '/')
		return (custom_error("Expected / in indices declaration\n"));
	parser->line++;
	if (!*parser->line || valid_int(parser->line))
		return (custom_error("Invalid vertex pos\n"));
	index.uv = (unsigned int)ft_atoi(parser->line);
	parser->line = skip_number(parser->line);
	if (!*parser->line || *parser->line == ' ' || *parser->line == '\r')
		return (set_new_index(index, parser));
	if (*parser->line != '/')
		return (custom_error("Expected / in indices declaration\n"));
	parser->line++;
	if (!*parser->line || valid_int(parser->line))
		return (custom_error("Invalid vertex pos\n"));
	index.norm = (unsigned int)ft_atoi(parser->line);
	parser->line = skip_number(parser->line);
	return (set_new_index(index, parser));
}

int		init_vertex(unsigned int i, t_obj_parser *parser,
t_object *object)
{
	unsigned int	k;

	k = 0;
	//ft_printf("Initializing vertex %d/%d/%d\n", parser->face_indices[i].pos,
	//parser->face_indices[i].uv, parser->face_indices[i].norm);
	while (k < parser->nb_unique_indices)
	{
		if (parser->unique_indices[k].pos == parser->face_indices[i].pos
			&& parser->unique_indices[k].uv == parser->face_indices[i].uv
			&& parser->unique_indices[k].norm == parser->face_indices[i].norm)
		{
			object->indices[object->nb_indices] = k;
			return (0);
		}
		k++;
	}
	if (!(object->vertices = (t_vertex*)realloc(object->vertices,
		(unsigned int)sizeof(t_vertex) * (++object->nb_vertices))))
			return (custom_error("Failed to realloc vertices"));
	if (!(parser->unique_indices = (t_index*)realloc(parser->unique_indices,
		(unsigned int)sizeof(t_index) * (++parser->nb_unique_indices))))
			return (custom_error("Failed to realloc vertices"));
	parser->unique_indices[parser->nb_unique_indices - 1] =
	parser->face_indices[i];
	object->vertices[object->nb_vertices - 1].pos =
	parser->pos[parser->face_indices[i].pos - 1];
	if (parser->face_indices[i].norm == 0)
	{
		if (parser->face_indices[i].pos - 1 < parser->nb_norm)
			object->vertices[object->nb_vertices - 1].norm =
			parser->norm[parser->face_indices[i].pos - 1];
		else
			object->vertices[object->nb_vertices - 1].norm =
			new_v3(1.0f, 1.0f, 1.0f);
	}
	else
		object->vertices[object->nb_vertices - 1].norm =
		parser->norm[parser->face_indices[i].norm- 1];
	if (parser->face_indices[i].uv == 0)
	{
		if (parser->face_indices[i].pos - 1 < parser->nb_tex)
			object->vertices[object->nb_vertices - 1].text =
			parser->tex[parser->face_indices[i].pos - 1];
		else
			object->vertices[object->nb_vertices - 1].text =
			new_v2(1.0f / (float)(i + 1), 1.0f / (float)(i + 1));
	}
	else
		object->vertices[object->nb_vertices - 1].text =
		parser->tex[parser->face_indices[i].uv - 1];
	//ft_printf("Nb uniques = %d\n", parser->nb_unique_indices);
	object->indices[object->nb_indices] = parser->nb_unique_indices - 1;
	/*ft_printf("Adding vertex %f %f %f\n",
	object->vertices[object->nb_vertices - 1].pos.x,
	object->vertices[object->nb_vertices - 1].pos.y,
	object->vertices[object->nb_vertices - 1].pos.z);*/
	return (0);
}

int		init_triangle_with_index(unsigned int i, t_obj_parser *parser,
t_object *object)
{
	if (!(object->indices = (unsigned int*)realloc(object->indices,
		(unsigned int)sizeof(unsigned int) * (object->nb_indices + 3))))
		return(custom_error("Failed to realloc vertices"));
	if (init_vertex(0, parser, object))
		return (-1);
		object->nb_indices++;
	if (init_vertex(i + 1, parser, object))
		return (-1);
		object->nb_indices++;
	if (init_vertex(i + 2, parser, object))
		return (-1);
	object->nb_indices++;
	return (0);
}

int		init_face(t_obj_parser *parser, t_object *object)
{
	unsigned int	i;

	i = 0;
	while (i < parser->face_size - 2)
	{
		if (init_triangle_with_index(i, parser, object))
			return (-1);
		i++;
	}
	return (0);
}

int		parse_index(t_obj_parser *parser, t_object *object, t_env *env)
{
	(void)env;
	parser->line++;
	if (!*parser->line)
		return (-1);
	parser->line = skip_spaces(parser->line);
	parser->face_size = 0;
	while (*parser->line)
	{
		if (parse_current_index(parser))
			return (-1);
		if (*parser->line)
			parser->line++;
	}
	/*unsigned int i = 0;
	ft_printf("Current face: ");
	while (i < parser->face_size)
	{
		ft_printf("%d/%d/%d ", parser->face_indices[i].pos,
		parser->face_indices[i].uv, parser->face_indices[i].norm);
		i++;
	}
	ft_printf("\n");*/
	if (init_face(parser, object))
		return (-1);
	return (0);
}

int		parse_normal(t_obj_parser *parser, t_object *object, t_env *env)
{
	t_v3	normal;

	(void)object;
	//ft_printf("NORMAL: ");
	parser->line++;
	if (!*parser->line)
		return (-1);
	parser->line = skip_spaces(parser->line);
	if (!*parser->line || valid_double(parser->line))
		return (-1);
	normal.x = (float)ft_atof(parser->line);
	//ft_printf("x = %f", normal.x);
	parser->line = skip_number(parser->line);
	parser->line = skip_spaces(parser->line);
	if (!*parser->line || valid_double(parser->line))
		return (-1);
	normal.y = (float)ft_atof(parser->line);
	//ft_printf(" y = %f", normal.y);
	parser->line = skip_number(parser->line);
	parser->line = skip_spaces(parser->line);
	if (!*parser->line || valid_double(parser->line))
		return (-1);
	normal.z = (float)ft_atof(parser->line);
	//ft_printf(" z = %f\n", normal.z);
	if (!(parser->norm = (t_v3*)realloc(parser->norm,
		(unsigned int)sizeof(t_v3) * ++parser->nb_norm)))
		ft_fatal_error("Failed to realloc vertices", env);
	parser->norm[parser->nb_norm - 1] = normal;
	return (0);
}

int		parse_uv(t_obj_parser *parser, t_object *object, t_env *env)
{
	t_v2	tex;

	//ft_printf("TEXTURE ");
	(void)object;
	parser->line++;
	if (!*parser->line)
		return (-1);
	parser->line = skip_spaces(parser->line);
	if (!*parser->line || valid_double(parser->line))
		return (-1);
	tex.x = (float)ft_atof(parser->line);
	//ft_printf("x = %f", tex.x);
	parser->line = skip_number(parser->line);
	parser->line = skip_spaces(parser->line);
	if (!*parser->line || valid_double(parser->line))
		return (-1);
	tex.y = (float)ft_atof(parser->line);
	//ft_printf(" y = %f\n", tex.y);
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
	//ft_printf("VERTEX ");
	if (!*parser->line)
		return (-1);
	parser->line = skip_spaces(parser->line);
	if (!*parser->line || valid_double(parser->line))
		return (-1);
	vertex.x = (float)ft_atof(parser->line);
	//ft_printf("x = %f", vertex.x);
	parser->line = skip_number(parser->line);
	parser->line = skip_spaces(parser->line);
	if (!*parser->line || valid_double(parser->line))
		return (-1);
	vertex.y = (float)ft_atof(parser->line);
	//ft_printf(" y = %f", vertex.y);
	parser->line = skip_number(parser->line);
	parser->line = skip_spaces(parser->line);
	if (!*parser->line || valid_double(parser->line))
		return (-1);
	vertex.z = (float)ft_atof(parser->line);
	//ft_printf(" z = %f\n", vertex.z);
	if (!(parser->pos = (t_v3*)realloc(parser->pos,
		(unsigned int)sizeof(t_v3) * ++parser->nb_vertices)))
		ft_fatal_error("Failed to realloc vertices", env);
	parser->pos[parser->nb_vertices - 1] = vertex;
	return (0);
}

int		parse_object_line(t_obj_parser *parser, t_object *object, t_env *env)
{
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
	ft_memdel((void**)&parser->face_indices);
	ft_memdel((void**)&parser->unique_indices);
	close(parser->fd);
}

int		parse_object(const char *source_file, t_object *object, t_env *env)
{
	int				ret;
	char			*tmp;
	t_obj_parser	parser;

	ret = 0;
	ft_bzero(&parser, sizeof(parser));
	if ((parser.fd = open(source_file, O_RDONLY)) < 0)
		return (custom_error("Could not open \"%s\"\n", source_file));
	while ((ret = get_next_line(parser.fd, &parser.line)))
	{
		//ft_printf("Reading %s\n", parser.line);
		tmp = parser.line;
		if (parse_object_line(&parser, object, env))
		{
			free_obj_parser(&parser);
			ft_strdel(&tmp);
			return (custom_error("Parsing error in \"%s\"\n", source_file));
		}
		ft_strdel(&tmp);
	}
	scale_new_object(object);
	free_obj_parser(&parser);
	return (0);
}
