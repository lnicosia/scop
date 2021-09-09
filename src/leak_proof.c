/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leak_proof.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 18:19:28 by lnicosia          #+#    #+#             */
/*   Updated: 2021/09/09 11:38:59 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>
#include "../lib/bmp_parser/includes/bmp_parser.h"

int	glfw_test()
{
	glfwInit();
	GLFWwindow *window = glfwCreateWindow(900, 900, "leak proof", NULL, NULL);
	glfwDestroyWindow(window);
	glfwTerminate();
	return (0);
}

int	bmp_test()
{
	t_texture texture;
	if (parse_bmp("resources/textures/container.bmp", &texture))
	{
		texture.invalid = 1;
		return (custom_error("Failed to parse bmp\n"));
	}
	ft_memdel((void**)&texture.pixels);
	return (0);
}

int	without_mipmap_test()
{
	unsigned int	tab[1];
	glfwInit();
	GLFWwindow *window = glfwCreateWindow(900, 900, "leak proof", NULL, NULL);
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		return (custom_error("Failed to init glad"));
	t_texture texture;
	if (parse_bmp("resources/textures/container.bmp", &texture))
	{
		texture.invalid = 1;
		return (custom_error("Failed to parse bmp\n"));
	}
	glGenTextures(1, &tab[0]);
	glBindTexture(GL_TEXTURE_2D, tab[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture.w, texture.h, 0, GL_RGB,
	GL_UNSIGNED_BYTE, texture.pixels);
	glDeleteTextures(1, tab);
	ft_memdel((void**)&texture.pixels);
	glfwDestroyWindow(window);
	glfwTerminate();
	return (0);
}

int	complete_test()
{
	unsigned int	tab[1];
	glfwInit();
	GLFWwindow *window = glfwCreateWindow(900, 900, "leak proof", NULL, NULL);
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		return (custom_error("Failed to init glad"));
	t_texture texture;
	if (parse_bmp("resources/textures/container.bmp", &texture))
	{
		texture.invalid = 1;
		return (custom_error("Failed to parse bmp\n"));
	}
	glGenTextures(1, &tab[0]);
	glBindTexture(GL_TEXTURE_2D, tab[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture.w, texture.h, 0, GL_RGB,
	GL_UNSIGNED_BYTE, texture.pixels);
	glGenerateMipmap(GL_TEXTURE_2D);
	glDeleteTextures(1, tab);
	ft_memdel((void**)&texture.pixels);
	glfwDestroyWindow(window);
	glfwTerminate();
	return (0);
}

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		ft_printf("usage:\n'1' for glfw init/terminate test\n");
		ft_printf("'2' for bmp parsing test\n");
		ft_printf("'3' complete test without mipmap\n");
		ft_printf("'4' complete test with mipmap\n");
		return (-1);
	}
	int opt = ft_atoi(av[1]);
	switch (opt)
	{
		case 1:
			ft_printf("Test 1 -\nglfwInit(), glfwCreateWindow(), then glfwDestroyWindow() and glfwTerminate().\n");
			return (glfw_test());
		case 2:
			ft_printf("Test 2 -\nparse_bmp() and free its pixels.\n");
			return (bmp_test());
		case 3:
			ft_printf("Test 3 -\nInit glfw, window, parse a bmp and generate then delete a texture WITHOUT mipmap.\n");
			return (without_mipmap_test());
		case 4:
			ft_printf("Test 4 -\nInit glfw, window, parse a bmp and generate then delete a texture WITH mipmap\n");
			return (complete_test());
		default:
			ft_printf("usage:\n'1' for glfw init/terminate test\n");
			ft_printf("'2' for bmp parsing test\n");
			ft_printf("'3' complete test without mipmap\n");
			ft_printf("'4' complete test with mipmap\n");
			return (0);
	}
}