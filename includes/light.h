/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 11:56:31 by lnicosia          #+#    #+#             */
/*   Updated: 2021/09/09 17:01:20 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include "libmft.h"

void	set_ambient(unsigned int shader, t_v3 value);
void	set_diffuse(unsigned int shader, t_v3 value);
void	set_specular(unsigned int shader, t_v3 value);

#endif 