/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_triangle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 12:28:54 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/11 13:59:13 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"

int		draw_triangle(t_env *env)
{
	float			vertices[9];
	unsigned int	vbo;
	unsigned int	vertex_shader;
	const char		*vertex_shader_source = "#version 330 core\n"
	"layout (location = 0) in ver3 aPos;\n"
	"void main()\n"
	"{\n"
	"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0)\n"
	"}\0";

	(void)env;
	vertices[0] = -0.5f;
	vertices[1] = -0.5f;
	vertices[2] = 0.0f;
	vertices[3] = 0.5f;
	vertices[4] = -0.5f;
	vertices[5] = 0.0f;
	vertices[6] = 0.0f;
	vertices[7] = 0.5f;
	vertices[8] = 0.0f;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	if (vertex_shader == 0)
		return (custom_error("Failed to init vertex shader\n"));
	glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
	glCompileShader(vertex_shader);
	return (0);
}
