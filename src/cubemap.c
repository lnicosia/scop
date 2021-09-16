/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubemap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 15:09:27 by lnicosia          #+#    #+#             */
/*   Updated: 2021/09/16 09:56:26 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "cubemap.h"
#include "bmp_parser.h"

void	print_cubemap(t_cubemap *cubemap)
{
	ft_printf("Cubemap:\n");
	ft_printf("Texture id = %d\n", cubemap->texture);
	ft_printf("Texture vao = %d\n", cubemap->vao);
	ft_printf("Texture vbo = %d\n", cubemap->vbo);
}

int		init_skybox_buffers(t_env *env)
{
	float skybox_vertices[] = {
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
	};
	glGenVertexArrays(1, &env->cubemaps[env->cubemap_count].vao);
	glGenBuffers(1, &env->cubemaps[env->cubemap_count].vbo);
	glBindVertexArray(env->cubemaps[env->cubemap_count].vao);
	glBindBuffer(GL_ARRAY_BUFFER, env->cubemaps[env->cubemap_count].vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skybox_vertices), skybox_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	return (0);
}

int		init_cubemap(char *files[6], int flip[6], GLenum format, t_env *env)
{
	init_skybox_buffers(env);
	glGenTextures(1, &env->cubemaps[env->cubemap_count].texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, env->cubemaps[env->cubemap_count].texture);
	ft_printf("Init cubemap texture id = %d\n", env->cubemaps[env->cubemap_count].texture);
	for (unsigned int i = 0; i < 6; i++)
	{
		t_texture	texture;

		if (flip[i] == 1)
		{
			if (parse_bmp_flipped(files[i], &texture))
			{
				texture.invalid = 1;
				return (custom_error("Failed to parse cubemap\n"));
			}
		}
		else 
		{
			if (parse_bmp(files[i], &texture))
			{
				texture.invalid = 1;
				return (custom_error("Failed to parse cubemap\n"));
			}
		}
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
		0, GL_RGB, texture.w, texture.h, 0,
		format, GL_UNSIGNED_BYTE, texture.pixels);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		ft_memdel((void**)&texture.pixels);
	}
	ft_printf("Cubemap composed of\n'%s'\n'%s'\n'%s'\n'%s'\n'%s'\n'%s'\nloaded\n",
	files[0], files[1], files[2], files[3], files[4], files[5]);
	env->cubemap_count++;
	return (0);
}

int		draw_skybox(t_cubemap *skybox, unsigned int shader, t_env *env)
{
	glDepthFunc(GL_LEQUAL);
	glUseProgram(shader);
	float	view[] = 
	{
		env->look_at_matrix[0], env->look_at_matrix[1], env->look_at_matrix[2], 0,
		env->look_at_matrix[4], env->look_at_matrix[5], env->look_at_matrix[6], 0,
		env->look_at_matrix[8], env->look_at_matrix[9], env->look_at_matrix[10], 0,
		0, 0, 0, 1
	};
	glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_TRUE,
	view);
	glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_TRUE,
	env->projection_matrix);
	glUniform1i(glGetUniformLocation(shader, "cubemap"), 0);
	glBindVertexArray(skybox->vao);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox->texture);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS);
	return (0);
}