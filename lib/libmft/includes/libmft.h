/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmft.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 22:16:18 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/17 11:21:10 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBMFT_H
# define LIBMFT_H

typedef struct		s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct		s_v2
{
	float			x;
	float			y;
}					t_v2;

typedef struct		s_v3
{
	float			x;
	float			y;
	float			z;
}					t_v3;

typedef struct		s_v4
{
	float			x;
	float			y;
	float			z;
	float			w;
}					t_v4;

typedef struct		s_circle_vars
{
	double			a;
	double			b;
	double			c;
}					t_circle_vars;

typedef	struct		s_segment
{
	t_v2			p1;
	t_v2			p2;
}					t_segment;

typedef	struct		s_plane
{
	double			d;
	t_v3			norm;
	char			padding[4];
}					t_plane;

typedef struct		s_complex
{
	double			r;
	double			i;
}					t_complex;

/*
** Vector/Matrix utils
*/

t_point				new_point(int x, int y);
t_v2				new_v2(float x, float y);
t_v3				new_v3(float x, float y, float z);
void				translate(float matrix[16], t_v3 translation);
void				scale(float matrix[16], t_v3 scale);
void    			rotate_x(float matrix[16], float angle);
void    			rotate_y(float matrix[16], float angle);
void    			rotate_z(float matrix[16], float angle);
void				reset_matrix(float matrix[16]);
void				print_matrix(float matrix[16]);

/*
** Geometry
*/

t_v2				get_intersection(t_v2 p1, t_v2 p2, t_v2 p3, t_v2 p4);
int					segments_intersect(t_v2 p1, t_v2 p2, t_v2 p3, t_v2 p4);
int					check_line_intersection(t_v2 p1, t_v2 p2, t_v2 p3,
t_v2 p4);
t_plane				new_plane(t_v3 p1, t_v3 p2, t_v3 p3);
t_v3				get_intersection_line_plane(t_v3 p1, t_v3 p2,
t_plane plane, t_v3 p3);

/*
** Complex numbers
*/

t_complex			ft_cadd(t_complex c1, t_complex c2);
t_complex			ft_csub(t_complex c1, t_complex c2);
t_complex			ft_cmul(t_complex c1, t_complex c2);
t_complex			ft_cdiv(t_complex c1, t_complex c2);
t_complex			ft_radd(double r, t_complex c);
t_complex			ft_rsub(double r, t_complex c);
t_complex			ft_rmul(double r, t_complex c);
t_complex			ft_rdiv(double r, t_complex c);
t_complex			ft_cpow(t_complex c1, int pow);
t_complex			ft_csin(t_complex c);
t_complex			ft_cscos(t_complex c);
t_complex			ft_cconj(t_complex c);
t_complex			new_complex(double r, double i);

/*
** Angle utils
*/

float				to_radians(float degrees);
float				to_degrees(float radians);

#endif