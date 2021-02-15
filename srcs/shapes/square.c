/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:12:46 by ndemont           #+#    #+#             */
/*   Updated: 2021/02/15 19:11:20 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <geometry.h>

float		inter_sq(t_ray ray, t_object sq, t_vector *inter, t_vector *normal)
{
	float		t;
	t_vector	x;
	t_vector	y;
	t_vector	l;
	int			check;

	*normal = get_normalized(sq.d);
	check = 0;
	t = scalaire(v_minus_v(sq.o, ray.o), *normal) / scalaire(ray.d, *normal);
	if (t >= 0)
	{
		x = get_normalized(v_dot_v(init_vector(0, 1, 0), sq.d));
		if (sq.d.coord[1] == 1)
			x = get_normalized(init_vector(1, 0, 0));
		y = get_normalized(v_dot_v(x, sq.d));
		*inter = v_plus_v(ray.o, v_mult_i(ray.d, t));
		sq.h /= 2;
		l = v_minus_v(*inter, sq.o);
		if (fabs(scalaire(l, x)) < sq.h)
			if (fabs(scalaire(l, y)) < sq.h)
				check = 1;
	}
	if (!check)
		t = 1E99;
	return (t);
}
