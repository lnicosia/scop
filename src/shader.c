/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 21:06:54 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/13 00:10:19 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>

char	*read_shader(const char *file)
{
	int			fd;
	ssize_t		ret;
	size_t		size;
	char		buffer[4096];
	char		*res;

	size = 0;
	res = 0;
	if ((fd = open(file, O_RDONLY)) == -1)
	{
		custom_error("{yellow}Could not open \"%s\"{reset}\n", file);
		return (0);
	}
	while ((ret = read(fd, buffer, 4096)) && size < 1000000000)
	{
		buffer[ret] = 0;
		res = ft_strjoin_free(res, buffer);
		size += ret;
	}
	ft_printf("{blue}Shader \"%s\":{reset}\n%s\n", file, res);
	if (close(fd))
		custom_error("{yellow}Could not close \"%s\"{reset}\n", file);
	return (res);
}

int		init_pipeline_shader(GLenum type, const char *file, t_env *env)
{
	unsigned int	shader;
	const char		*shader_source;

	shader_source = read_shader(file);
	shader = glCreateShader(type);
	glShaderSource(shader, 1, &shader_source, NULL);
	glCompileShader(shader);
	env->success = GLFW_FALSE;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &env->success);
	ft_memdel((void**)&shader_source);
	if (env->success != GLFW_TRUE)
	{
		glGetShaderInfoLog(shader, 512, NULL, env->log);
		custom_error("{yellow}Failed to compile shader\n");
		return (custom_error(env->log));
	}
	return (shader);
}

int		init_program(unsigned int vertex_shader, unsigned int fragment_shader,
t_env *env)
{
	if ((env->tuto_shader = glCreateProgram()) == 0)
		return (custom_error("Failed to create shader program\n"));
	glAttachShader(env->tuto_shader, vertex_shader);
	glAttachShader(env->tuto_shader, fragment_shader);
	glLinkProgram(env->tuto_shader);
	env->success = GL_FALSE;
	glGetProgramiv(env->tuto_shader, GL_LINK_STATUS, &env->success);
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
	if (env->success != GL_TRUE)
	{
		glGetProgramInfoLog(env->tuto_shader, 512, NULL, env->log);
		custom_error("Failed to compile shader program\n");
		return (custom_error(env->log));
	}
	return (0);
}
