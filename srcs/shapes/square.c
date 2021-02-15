/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:12:46 by ndemont           #+#    #+#             */
/*   Updated: 2021/02/15 11:33:16 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <geometry.h>

float		inter_sq(t_ray ray, t_object sq, t_vector *inter, t_vector *normal)
{
	float		t;
	t_vector	v;
	int			check;
	t_vector	l;

	*normal = get_normalized(sq.d);
	check = 0;
	v = v_minus_v(sq.o, ray.o);
	t = scalaire(v, *normal) / scalaire(ray.d, *normal);
	if (t >= 0)
	{
		*inter = v_plus_v(ray.o, v_mult_i(ray.d, t));
		sq.h /= 2;
		l = v_minus_v(*inter, sq.o);
		if ((fabs(l.coord[0]) <= sq.h) && (fabs(l.coord[1]) <=  sq.h) && (fabs(l.coord[2]) <=  sq.h))
			check = 1;
	}
	if (!check)
		t = 1E99;
	return (t);
}
