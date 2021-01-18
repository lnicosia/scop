/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_chars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 19:36:55 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/18 19:36:56 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*skip_number(char *line)
{
	if (*line && *line == '-')
		line++;
	while (*line && (*line <= '9' && *line >= '0'))
		line++;
	if (*line && *line == '.')
	{
		line++;
		while (*line && (*line <= '9' && *line >= '0'))
			line++;
	}
	return (line);
}

char	*skip_hexa(char *line)
{
	while (*line && ((*line <= '9' && *line >= '0')
		|| (*line >= 'A' && *line <= 'F')
		|| (*line >= 'a' && *line <= 'f')))
		line++;
	return (line);
}

char	*skip_spaces(char *line)
{
	while (*line && *line == ' ')
		line++;
	return (line);
}