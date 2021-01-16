/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrixrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 14:47:31 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/16 14:49:08 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	reset_matrix(float matrix[16])
{
	//double	angle = 1;
	matrix[0] = 1.0f;//cos(angle);
	matrix[1] = 0.0f;//-sin(angle);
	matrix[2] = 0.0f;
	matrix[3] = 0.0f;
	matrix[4] = 0;//sin(angle);
	matrix[5] = 1.0f;//cos(angle);
	matrix[6] = 0.0f;
	matrix[7] = 0.0f;
	matrix[8] = 0.0f;
	matrix[9] = 0.0f;
	matrix[10] = 1.0f;
	matrix[11] = 0.0f;
	matrix[12] = 0.0f;
	matrix[13] = 0.0f;
	matrix[14] = 0.0f;
	matrix[15] = 1.0f;
}