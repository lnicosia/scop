/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 23:48:08 by lnicosia          #+#    #+#             */
/*   Updated: 2021/09/17 11:06:16 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft.h"
#include "scop.h"
#include "obj_parser.h"

int		scale_and_center_object(t_obj_parser *parser, t_object *object)
{
	t_v3			min;
	t_v3			max;
	unsigned int	i, j;
	float			scale;

	min = object->meshes[0].vertices[0].pos;
	max = object->meshes[0].vertices[0].pos;
	j = 0;
	while (j < object->nb_meshes)
	{
		i = 0;
		while (i < object->meshes[j].nb_vertices)
		{
			if (object->meshes[j].vertices[i].pos.x < min.x)
				min.x = object->meshes[j].vertices[i].pos.x;
			if (object->meshes[j].vertices[i].pos.x > max.x)
				max.x = object->meshes[j].vertices[i].pos.x;
			if (object->meshes[j].vertices[i].pos.y < min.y)
				min.y = object->meshes[j].vertices[i].pos.y;
			if (object->meshes[j].vertices[i].pos.y > max.y)
				max.y = object->meshes[j].vertices[i].pos.y;	
			if (object->meshes[j].vertices[i].pos.z < min.z)
				min.z = object->meshes[j].vertices[i].pos.z;
			if (object->meshes[j].vertices[i].pos.z > max.z)
				max.z = object->meshes[j].vertices[i].pos.z;	
			i++;
		}
		j++;
	}
	object->range.x = max.x - min.x;
	object->range.y = max.y - min.y;
	object->range.z = max.z - min.z;
	float	div_x = 1 / object->range.x;
	float	div_y = 1 / object->range.y;
	float	div_z = 1 / object->range.z;
	float	min_axis = (object->range.x < object->range.y) ? object->range.x : object->range.y;
	min_axis = (min_axis < object->range.z) ? min_axis : object->range.z;
	float	max_axis = (object->range.x > object->range.y) ? object->range.x : object->range.y;
	max_axis = (max_axis > object->range.z) ? max_axis : object->range.z;
	scale = (float)ft_fmax(object->range.x, object->range.y);
	scale = (float)ft_fmax(scale, object->range.z);
	j = 0;
	while (j < object->nb_meshes)
	{
		i = 0;
		while (i < object->meshes[j].nb_vertices)
		{
			if (parser->mode == GENERATE_UV || parser->uv_exists[i + j] == NO)
			{
				if (max_axis == object->range.x)
				{
					object->meshes[j].vertices[i].text.x =
					(object->meshes[j].vertices[i].pos.x - min.x) * div_z;
					if (min_axis == object->range.y)
					{
						object->meshes[j].vertices[i].text.y =
						(object->meshes[j].vertices[i].pos.z - min.z) * div_z;
					}
					else
					{
						object->meshes[j].vertices[i].text.y =
						(object->meshes[j].vertices[i].pos.y - min.y) * div_y;
					}
				}
				else if (max_axis == object->range.y)
				{
					object->meshes[j].vertices[i].text.x =
					(object->meshes[j].vertices[i].pos.y - min.y) * div_y;
					if (min_axis == object->range.x)
					{
						object->meshes[j].vertices[i].text.y =
						(object->meshes[j].vertices[i].pos.z - min.z) * div_z;
					}
					else
					{
						object->meshes[j].vertices[i].text.y =
						(object->meshes[j].vertices[i].pos.x - min.x) * div_x;
					}
				}
				else if (max_axis == object->range.z)
				{
					object->meshes[j].vertices[i].text.x =
					(object->meshes[j].vertices[i].pos.z - min.z) * div_z;
					if (min_axis == object->range.y)
					{
						object->meshes[j].vertices[i].text.y =
						(object->meshes[j].vertices[i].pos.x - min.x) * div_x;
					}
					else
					{
						object->meshes[j].vertices[i].text.y =
						(object->meshes[j].vertices[i].pos.y - min.y) * div_y;
					}
				}
				//ft_printf("Vertex %d: [%9f %9f %9f] [%9f %9f] uv [%d]\n", i + j,
				//object->meshes[j].vertices[i].pos.x, object->meshes[j].vertices[i].pos.y,
				//object->meshes[j].vertices[i].pos.z, object->meshes[j].vertices[i].text.x,
				//object->meshes[j].vertices[i].text.y, parser->uv_exists[i + j]);
			}
			object->meshes[j].vertices[i].pos.x -= object->range.x / 2.0f + min.x;
			object->meshes[j].vertices[i].pos.y -= object->range.y / 2.0f + min.y;
			object->meshes[j].vertices[i].pos.z -= object->range.z / 2.0f + min.z;

			object->meshes[j].vertices[i].pos.x /= scale;
			object->meshes[j].vertices[i].pos.y /= scale;
			object->meshes[j].vertices[i].pos.z /= scale;
			i++;
		}
		j++;
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
	if (!*parser->line || valid_int(parser->line))
		return (custom_error("Invalid vertex pos at line %d\n", parser->line_nb));
	index.pos = (unsigned int)ft_atoi(parser->line);
	if (index.pos > parser->nb_vertices)
		return (custom_error("Invalid vertex number (%d) at line %d\n", index.pos, parser->line_nb));
	parser->line = skip_number(parser->line);
	if (!*parser->line || *parser->line == ' ' || *parser->line == '\r')
		return (set_new_index(index, parser));
	if (*parser->line != '/')
		return (custom_error("Expected / in indices declaration at line %d\n", parser->line_nb));
	parser->line++;
	if (!*parser->line || valid_int(parser->line))
		return (custom_error("Invalid vertex pos at line %d\n", parser->line_nb));
	index.uv = (unsigned int)ft_atoi(parser->line);
	if (index.uv > parser->nb_tex)
		return (custom_error("Invalid uv number (%d) at line %d\n", index.uv, parser->line_nb));
	parser->line = skip_number(parser->line);
	if (!*parser->line || *parser->line == ' ' || *parser->line == '\r')
		return (set_new_index(index, parser));
	if (*parser->line != '/')
		return (custom_error("Expected / in indices declaration at line %d\n", parser->line_nb));
	parser->line++;
	if (!*parser->line || valid_int(parser->line))
		return (custom_error("Invalid vertex pos at line %d\n", parser->line_nb));
	index.norm = (unsigned int)ft_atoi(parser->line);
	if (index.norm > parser->nb_norm)
		return (custom_error("Invalid normal number (%d) at line %d\n",
			index.norm, parser->line_nb));
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
	//ft_printf("There are %d unique faces\n", parser->nb_unique_indices);
	while (k < parser->nb_unique_indices)
	{
		if (parser->unique_indices[k].pos == parser->face_indices[i].pos
			&& parser->unique_indices[k].uv == parser->face_indices[i].uv
			&& parser->unique_indices[k].norm == parser->face_indices[i].norm)
		{
			object->meshes[parser->current_mesh].
			indices[object->meshes[parser->current_mesh].nb_indices] = k;
			return (0);
		}
		k++;
	}
	if (!(object->meshes[parser->current_mesh].vertices = (t_vertex*)realloc(object->meshes[parser->current_mesh].vertices,
		(unsigned int)sizeof(t_vertex) * (++object->meshes[parser->current_mesh].nb_vertices))))
			return (custom_error("Failed to realloc vertices"));
	if (!(parser->uv_exists = (char*)realloc(parser->uv_exists,
		(unsigned int)sizeof(char) * (object->meshes[parser->current_mesh].nb_vertices))))
			return (custom_error("Failed to realloc vertices"));
	parser->uv_exists[object->meshes[parser->current_mesh].nb_vertices - 1] = YES;
	if (parser->face_indices[i].uv == 0)
		parser->uv_exists[object->meshes[parser->current_mesh].nb_vertices - 1] = NO;
	if (!(parser->unique_indices = (t_index*)realloc(parser->unique_indices,
		(unsigned int)sizeof(t_index) * (++parser->nb_unique_indices))))
			return (custom_error("Failed to realloc vertices"));
	parser->unique_indices[parser->nb_unique_indices - 1] =
	parser->face_indices[i];
	object->meshes[parser->current_mesh].vertices[object->meshes[parser->current_mesh].nb_vertices - 1].pos =
	parser->pos[parser->face_indices[i].pos - 1];
	if (parser->face_indices[i].norm == 0)
	{
		if (parser->face_indices[i].pos - 1 < parser->nb_norm)
			object->meshes[parser->current_mesh].vertices[object->meshes[parser->current_mesh].nb_vertices - 1].norm =
			parser->norm[parser->face_indices[i].pos - 1];
		else
			object->meshes[parser->current_mesh].vertices[object->meshes[parser->current_mesh].nb_vertices - 1].norm =
			new_v3(1.0f, 1.0f, 1.0f);
	}
	else
		object->meshes[parser->current_mesh].vertices[object->meshes[parser->current_mesh].nb_vertices - 1].norm =
		parser->norm[parser->face_indices[i].norm - 1];
	if (parser->face_indices[i].uv == 0)
	{
		if (parser->face_indices[i].pos - 1 < parser->nb_tex)
			object->meshes[parser->current_mesh].vertices[object->meshes[parser->current_mesh].nb_vertices - 1].text =
			parser->tex[parser->face_indices[i].pos - 1];
		else
			object->meshes[parser->current_mesh].vertices[object->meshes[parser->current_mesh].nb_vertices - 1].text = new_v2(0.0f, 0.0f);
			//new_v2(1.0f / (float)(i + 1), 1.0f / (float)(i + 1));
	}
	else
		object->meshes[parser->current_mesh].vertices[object->meshes[parser->current_mesh].nb_vertices - 1].text =
		parser->tex[parser->face_indices[i].uv - 1];
	//ft_printf("Nb uniques = %d\n", parser->nb_unique_indices);
	object->meshes[parser->current_mesh].indices[object->meshes[parser->current_mesh].nb_indices] =
	parser->nb_unique_indices - 1;
	/*ft_printf("Adding vertex %f %f %f\n",
	object->meshes[parser->current_mesh].vertices[object->meshes[parser->current_mesh].nb_vertices - 1].pos.x,
	object->meshes[parser->current_mesh].vertices[object->meshes[parser->current_mesh].nb_vertices - 1].pos.y,
	object->meshes[parser->current_mesh].vertices[object->meshes[parser->current_mesh].nb_vertices - 1].pos.z);*/
	return (0);
}

/*int		compute_uv(t_obj_parser *parser, t_object *object)
{
	(void)object;
	unsigned int i = 0;
	ft_printf("Current face: ");
	while (i < parser->face_size)
	{
		ft_printf("%d/%d/%d ", parser->face_indices[i].pos,
		parser->face_indices[i].uv, parser->face_indices[i].norm);
		i++;
	}
	ft_printf("\n");
	i = 0;
	while (i < parser->face_size)
	{
		ft_printf("v%d (f %d) = [%9f %9f %9f]\n", i,
		parser->face_indices[i].pos,
		parser->pos[parser->face_indices[i].pos - 1].x,
		parser->pos[parser->face_indices[i].pos - 1].y,
		parser->pos[parser->face_indices[i].pos - 1].z);
		i++;
	}

	i = 0;
	float	min_x = parser->pos[parser->face_indices[i].pos - 1].x;
	float	min_y = parser->pos[parser->face_indices[i].pos - 1].y;
	float	min_z = parser->pos[parser->face_indices[i].pos - 1].z;
	float	max_x = parser->pos[parser->face_indices[i].pos - 1].x;
	float	max_y = parser->pos[parser->face_indices[i].pos - 1].y;
	float	max_z = parser->pos[parser->face_indices[i].pos - 1].z;
	for (unsigned int j = 0; j < parser->face_size; j++)
	{
		if (parser->pos[parser->face_indices[i + j].pos - 1].x < min_x)
			min_x = parser->pos[parser->face_indices[i + j].pos - 1].x;
		if (parser->pos[parser->face_indices[i + j].pos - 1].y < min_y)
			min_y = parser->pos[parser->face_indices[i + j].pos - 1].y;
		if (parser->pos[parser->face_indices[i + j].pos - 1].z < min_z)
			min_z = parser->pos[parser->face_indices[i + j].pos - 1].z;
		if (parser->pos[parser->face_indices[i + j].pos - 1].x > max_x)
			max_x = parser->pos[parser->face_indices[i + j].pos - 1].x;
		if (parser->pos[parser->face_indices[i + j].pos - 1].y > max_y)
			max_y = parser->pos[parser->face_indices[i + j].pos - 1].y;
		if (parser->pos[parser->face_indices[i + j].pos - 1].z > max_z)
			max_z = parser->pos[parser->face_indices[i + j].pos - 1].z;
	}
	//ft_printf("Min x = %f\nMin y = %f\nMin z = %f\n", min_x, min_y, min_z);
	//ft_printf("Max x = %f\nMax y = %f\nMax z = %f\n", max_x, max_y, max_z);
	float	x_length = max_x - min_x;
	float	y_length = max_y - min_y;
	float	z_length = max_z - min_z;
	float	div_x = 1 / x_length;
	float	div_y = 1 / y_length;
	float	div_z = 1 / z_length;
	ft_printf("X length = %f\n", x_length);
	ft_printf("Y length = %f\n", y_length);
	ft_printf("Z length = %f\n", z_length);
	float	min = (x_length < y_length) ? x_length : y_length;
	min = (min < z_length) ? min : z_length;
	if (min == x_length)
		ft_printf("X is the smallest\n");
	if (min == y_length)
		ft_printf("Y is the smallest\n");
	if (min == z_length)
		ft_printf("Z is the smallest\n");
	i = 0;
	while (i < parser->face_size)
	{
		unsigned int vertex_index = object->meshes[parser->current_mesh].nb_vertices - parser->face_size + i;
		ft_printf("Vertex %d (f %d)\n", vertex_index, parser->face_indices[i].pos);
		float	start_x = 0, start_y = 0, start_z = 0;
		(void)start_x;(void)start_y;(void)start_z;
		if (min == z_length)
		{
			if (parser->generated_uv[vertex_index].x == 0)
			{
				object->meshes[parser->current_mesh].vertices[vertex_index].text.x = 
				object->meshes[parser->current_mesh].vertices[vertex_index].pos.x * div_x;// + start_x;
				parser->generated_uv[vertex_index].x = 1;
			}
			else
			{
				ft_printf("U already generated: %f\n", object->meshes[parser->current_mesh].vertices[vertex_index].text.x);
				start_x = object->meshes[parser->current_mesh].vertices[vertex_index].text.x;
			}
			if (parser->generated_uv[vertex_index].y == 0)
			{
				object->meshes[parser->current_mesh].vertices[vertex_index].text.y = 
				object->meshes[parser->current_mesh].vertices[vertex_index].pos.y * div_y;// + start_y;
				parser->generated_uv[vertex_index].y = 1;
			}
			else
			{
				ft_printf("V already generated: %f\n", object->meshes[parser->current_mesh].vertices[vertex_index].text.y);
				start_y = object->meshes[parser->current_mesh].vertices[vertex_index].text.y;
			}
		}
		else if (min == x_length)
		{
			if (parser->generated_uv[vertex_index].x == 0)
			{
				object->meshes[parser->current_mesh].vertices[vertex_index].text.x = 
				object->meshes[parser->current_mesh].vertices[vertex_index].pos.z * div_y;// + start_z;
				parser->generated_uv[vertex_index].x = 1;
			}
			else
			{
				ft_printf("U already generated: %f\n", object->meshes[parser->current_mesh].vertices[vertex_index].text.x);
			}
			if (parser->generated_uv[vertex_index].y == 0)
			{
				object->meshes[parser->current_mesh].vertices[vertex_index].text.y = 
				object->meshes[parser->current_mesh].vertices[vertex_index].pos.y * div_z;// + start_y;
				parser->generated_uv[vertex_index].y = 1;
			}
			else
			{
				ft_printf("V already generated: %f\n", object->meshes[parser->current_mesh].vertices[vertex_index].text.y);
			}
		}
		else if (min == y_length)
		{
			if (parser->generated_uv[vertex_index].x == 0)
			{
				object->meshes[parser->current_mesh].vertices[vertex_index].text.x = 
				object->meshes[parser->current_mesh].vertices[vertex_index].pos.z * div_x;// + start_x;
				parser->generated_uv[vertex_index].x = 1;
			}
			else
			{
				ft_printf("U already generated: %f\n", object->meshes[parser->current_mesh].vertices[vertex_index].text.x);
				start_x = object->meshes[parser->current_mesh].vertices[vertex_index].text.x;
			}
			if (parser->generated_uv[vertex_index].y == 0)
			{
				object->meshes[parser->current_mesh].vertices[vertex_index].text.y = 
				object->meshes[parser->current_mesh].vertices[vertex_index].pos.x * div_z;// + start_z;
				parser->generated_uv[vertex_index].y = 1;
			}
			else
			{
				ft_printf("V already generated: %f\n", object->meshes[parser->current_mesh].vertices[vertex_index].text.y);
			}
		}
		//ft_printf("Vertex %d uv = [%9f %9f]\n", vertex_index + 1,
		//object->meshes[parser->current_mesh].vertices[vertex_index].text.x,
		//object->meshes[parser->current_mesh].vertices[vertex_index].text.y);
		i++;
	}
	return (0);
}*/

int		init_triangle_with_index(unsigned int i, t_obj_parser *parser,
t_object *object)
{
	if (!(object->meshes[parser->current_mesh].indices = (unsigned int*)realloc(object->meshes[parser->current_mesh].indices,
		sizeof(unsigned int) * (object->meshes[parser->current_mesh].nb_indices + 3))))
		return(custom_error("Failed to realloc vertices"));
	if (init_vertex(0, parser, object))
		return (-1);
		object->meshes[parser->current_mesh].nb_indices++;
	if (init_vertex(i + 1, parser, object))
		return (-1);
		object->meshes[parser->current_mesh].nb_indices++;
	if (init_vertex(i + 2, parser, object))
		return (-1);
	object->meshes[parser->current_mesh].nb_indices++;
	return (0);
}

int		init_face(t_obj_parser *parser, t_object *object)
{
	unsigned int	i;

	i = 0;
	while (i < parser->face_size - 2)
	{
		//ft_printf("New triangle\n");
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
	if (parser->face_size < 3)
		return (custom_error("Incorrect number of faces (%d) at line %d\n", parser->face_size, parser->line_nb));
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
	parser->last_line = FACE;
	return (0);
}

int		parse_normal(t_obj_parser *parser, t_object *object, t_env *env)
{
	t_v3	normal;

	(void)object;
	//ft_printf("NORMAL: ");
	parser->line++;
	if (!*parser->line)
		return (custom_error("Normal declaration at line %d is incorrect or incomplete\n", parser->line_nb));
	parser->line = skip_spaces(parser->line);
	if (!*parser->line || valid_double(parser->line))
		return (custom_error("Normal declaration at line %d is incorrect or incomplete\n", parser->line_nb));
	normal.x = (float)ft_atof(parser->line);
	//ft_printf("x = %f", normal.x);
	parser->line = skip_number(parser->line);
	parser->line = skip_spaces(parser->line);
	if (!*parser->line || valid_double(parser->line))
		return (custom_error("Normal declaration at line %d is incorrect or incomplete\n", parser->line_nb));
	normal.y = (float)ft_atof(parser->line);
	//ft_printf(" y = %f", normal.y);
	parser->line = skip_number(parser->line);
	parser->line = skip_spaces(parser->line);
	if (!*parser->line || valid_double(parser->line))
		return (custom_error("Normal declaration at line %d is incorrect or incomplete\n", parser->line_nb));
	normal.z = (float)ft_atof(parser->line);
	//ft_printf(" z = %f\n", normal.z);
	if (!(parser->norm = (t_v3*)realloc(parser->norm,
		(unsigned int)sizeof(t_v3) * ++parser->nb_norm)))
		ft_fatal_error("Failed to realloc vertices", env);
	parser->norm[parser->nb_norm - 1] = normal;
	parser->last_line = NORMAL;
	return (0);
}

int		parse_uv(t_obj_parser *parser, t_object *object, t_env *env)
{
	t_v2	tex;

	//ft_printf("TEXTURE ");
	(void)object;
	parser->line++;
	if (!*parser->line)
		return (custom_error("UV declaration at line %d is incorrect or incomplete\n", parser->line_nb));
	parser->line = skip_spaces(parser->line);
	if (!*parser->line || valid_double(parser->line))
		return (custom_error("UV declaration at line %d is incorrect or incomplete\n", parser->line_nb));
	tex.x = (float)ft_atof(parser->line);
	//ft_printf("x = %f", tex.x);
	parser->line = skip_number(parser->line);
	parser->line = skip_spaces(parser->line);
	if (!*parser->line || valid_double(parser->line))
		return (custom_error("UV declaration at line %d is incorrect or incomplete\n", parser->line_nb));
	tex.y = (float)ft_atof(parser->line);
	//ft_printf(" y = %f\n", tex.y);
	if (!(parser->tex = (t_v2*)realloc(parser->tex,
		(unsigned int)sizeof(t_v2) * ++parser->nb_tex)))
		ft_fatal_error("Failed to realloc vertices", env);
	parser->tex[parser->nb_tex - 1] = tex;
	parser->last_line = TEXTURE;
	return (0);
}

int		parse_vertex(t_obj_parser *parser, t_object *object, t_env *env)
{
	t_v3	vertex;

	(void)object;
	//ft_printf("VERTEX ");
	if (!*parser->line)
		return (custom_error("Vertex declaration at line %d is incorrect or incomplete\n", parser->line_nb));
	parser->line = skip_spaces(parser->line);
	if (!*parser->line || valid_double(parser->line))
		return (custom_error("Vertex declaration at line %d is incorrect or incomplete\n", parser->line_nb));
	vertex.x = (float)ft_atof(parser->line);
	//ft_printf("x = %f", vertex.x);
	parser->line = skip_number(parser->line);
	parser->line = skip_spaces(parser->line);
	if (!*parser->line || valid_double(parser->line))
		return (custom_error("Vertex declaration at line %d is incorrect or incomplete\n", parser->line_nb));	vertex.y = (float)ft_atof(parser->line);
	//ft_printf(" y = %f", vertex.y);
	parser->line = skip_number(parser->line);
	parser->line = skip_spaces(parser->line);
	if (!*parser->line || valid_double(parser->line))
		return (custom_error("Vertex declaration at line %d is incorrect or incomplete\n", parser->line_nb));
	vertex.z = (float)ft_atof(parser->line);
	//ft_printf(" z = %f\n", vertex.z);
	if (!(parser->pos = (t_v3*)realloc(parser->pos,
		sizeof(t_v3) * ++parser->nb_vertices)))
		ft_fatal_error("Failed to realloc vertices", env);
	parser->pos[parser->nb_vertices - 1] = vertex;
	parser->last_line = VERTEX;
	return (0);
}

int		parse_mtllib(t_obj_parser *parser, t_object *object, t_env *env)
{
	(void)env;
	(void)parser;
	(void)object;
	//ft_printf("Mat lib found: %s\n", parser->line);
	return (0);
}

int		new_mesh(t_obj_parser *parser, t_object *object)
{
	//ft_memdel((void**)&parser->unique_indices);
	//parser->nb_unique_indices = 0;
	//ft_printf("Mesh #%d:", object->nb_meshes);
	//ft_printf(" line %d: %s\n", parser->line_nb, parser->line);
	ft_memdel((void**)&parser->unique_indices);
	parser->nb_unique_indices = 0;
	if (object->nb_meshes > 0)
		object->nb_vertices += object->meshes[parser->current_mesh].nb_vertices;
	parser->current_mesh++;
	object->nb_meshes++;
	if (!(object->meshes = (t_mesh*)realloc(object->meshes, sizeof(t_mesh) * object->nb_meshes)))
		return (custom_error("realloc fail when allocating new object's meshes\n"));
	ft_bzero(&object->meshes[parser->current_mesh],
	sizeof(object->meshes[parser->current_mesh]));
	return (0);
}

int		parse_object_line(t_obj_parser *parser, t_object *object, t_env *env)
{
	// if last line is -1, it's the first mesh
	// and if it was a face, we have a new mesh
	if (parser->last_line == -1 ||
		(parser->last_line == FACE && *parser->line != 'f' && *parser->line != '#'))
	{
		if (new_mesh(parser, object))
			return (-1);
	}
	if (!parser->line)
		return (custom_error("Line %d is invalid\n", parser->line_nb));
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
	else if (ft_strnequ(parser->line, "mtllib", 6))
	{
		if (parse_mtllib(parser, object, env))
			return (custom_error("Error while parsing material lib\n"));
	}
	else
		parser->last_line = OTHER;
	return (0);
}

void	free_obj_parser(t_obj_parser *parser)
{
	ft_memdel((void**)&parser->pos);
	ft_memdel((void**)&parser->tex);
	ft_memdel((void**)&parser->norm);
	ft_memdel((void**)&parser->face_indices);
	ft_memdel((void**)&parser->unique_indices);
	ft_memdel((void**)&parser->uv_exists);
	if (close(parser->fd))
		custom_error("Could not close fd %d\n", parser->fd);
}

int		parse_object(const char *source_file, int mode, t_object *object, t_env *env)
{
	int				ret;
	char			*tmp;
	t_obj_parser	parser;

	ret = 0;
	ft_bzero(&parser, sizeof(parser));
	if ((parser.fd = open(source_file, O_RDONLY)) < 0)
		return (custom_error("Could not open \"%s\"\n", source_file));
	parser.line_nb = 1;
	parser.last_line = -1;
	parser.current_mesh = -1;
	parser.mode = mode;
	object->name = source_file;
	while ((ret = get_next_line(parser.fd, &parser.line)))
	{
		tmp = parser.line;
		if (parse_object_line(&parser, object, env))
		{
			free_obj_parser(&parser);
			free_object(object);
			ft_strdel(&tmp);
			return (custom_error("Parsing error in \"%s\"\n", source_file));
		}
		parser.line_nb++;
		ft_strdel(&tmp);
	}
	if (object->nb_meshes == 0)
		return (custom_error("Invalid object (no mesh)\n"));
	for (unsigned int i = 0; i < object->nb_meshes; i++)
	{
		if (object->meshes[i].nb_vertices < 3 || object->meshes[i].nb_indices < 1)
			return (custom_error("Invalid object (mesh %d has %d vertices and %d indices)\n",
			i, object->meshes[i].nb_vertices, object->meshes[i].nb_indices));
	}
	object->nb_vertices += object->meshes[parser.current_mesh].nb_vertices;
	scale_and_center_object(&parser, object);
	free_obj_parser(&parser);
	return (0);
}
