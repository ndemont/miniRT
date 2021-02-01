/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:12:46 by ndemont           #+#    #+#             */
/*   Updated: 2021/02/01 18:49:27 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <geometry.h>

float		inter_sq(t_ray ray, t_object sq, t_vector *inter, t_vector *normal)
{
	float		t;
	t_vector	v;
	int			count;
	t_vector	l2;
	t_vector	l;

	*normal = get_normalized(sq.d);
	count = 0;
	v = v_minus_v(sq.o, ray.o);
	t = scalaire(v, *normal) / scalaire(ray.d, *normal);
	if (t >= 0)
	{
		l = v_plus_i(sq.o, sq.h / 2);
		l2 = v_minus_i(sq.o, sq.h / 2);
		*inter = v_plus_v(ray.o, v_mult_i(ray.d, t));
		if (inter->coord[0] <= l.coord[0] && inter->coord[0] >= l2.coord[0])
			count++;
		if (inter->coord[1] <= l.coord[1] && inter->coord[1] >= l2.coord[1])
			count++;
		if (inter->coord[2] <= l.coord[2] && inter->coord[2] >= l2.coord[2])
			count++;
	}
	if (count != 3)
		t = 1E99;
	return (t);
}
