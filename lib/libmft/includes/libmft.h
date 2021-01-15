/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmft.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 22:16:18 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/15 13:22:26 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBMFT_h
# define LIBMFT_H

typedef struct		s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct		s_v2
{
	double			x;
	double			y;
}					t_v2;

typedef struct		s_v3
{
	double			x;
	double			y;
	double			z;
}					t_v3;

typedef struct		s_v4
{
	double			x;
	double			y;
	double			z;
	double			w;
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
	t_v3			norm;
	double			d;
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
t_v2				new_v2(double x, double y);
t_v3				new_v3(double x, double y, double z);
t_v4				translate(t_v4 vec, t_v3 translation);
t_v4				scale(t_v4 vec, t_v3 scale);
t_v4				rotate_x(t_v4 vec, double angle);
t_v4				rotate_y(t_v4 vec, double angle);
t_v4				rotate_z(t_v4 vec, double angle);

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

#endif