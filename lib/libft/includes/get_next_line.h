/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 18:23:24 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/22 13:40:35 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# define BUFF_SIZE 16384
#  define NEWLINE 10

typedef struct	s_read
{
	char	*str;
	int		fd;
	char	padding[4];
}				t_read;

int				get_next_line(const int fd, char **line);

#endif
