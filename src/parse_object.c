/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 23:48:08 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/17 23:59:00 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft.h"
#include "env.h"

int		parse_object_line(char *line, t_object *object)
{
	(void)line;
	(void)object;
	return (0);
}

int		parse_object(const char *source_file, t_object *object)
{
	int		fd;
	int		ret;
	char	*line;

	ret = 0;
	if ((fd = open(source_file, O_RDONLY)) < 0)
		return (custom_error("Could not open \"%s\"\n", source_file));
	while ((ret = get_next_line(fd, &line)))
	{
		if (parse_object_line(line, object))
			return (custom_error("Parsing error in \"%s\"\n", source_file));
		ft_strdel(&line);
	}
	return (0);
}