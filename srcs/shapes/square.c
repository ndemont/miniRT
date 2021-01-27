/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:12:46 by ndemont           #+#    #+#             */
/*   Updated: 2021/01/27 11:14:10 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <geometry.h>

float		inter_sq(t_ray ray, t_object sq, t_vector *inter, t_vector *normal)
{
	float		t;
	t_vector	v;
	int			count;

	*normal = sq.d;
	*normal = get_normalized(*normal);
	count = 0;
	v = v_minus_v(sq.o, ray.o);
	t = scalaire(v, *normal) / scalaire(ray.d, *normal);
	if (t >= 0)
	{
		*inter = v_plus_v(ray.o, v_mult_i(ray.d, t));
		if (inter->coord[0] <= sq.o.coord[0] + (sq.h / 2) && inter->coord[0] >= sq.o.coord[0] - (sq.h / 2))
			count++;
		if (inter->coord[1] <= sq.o.coord[1] + (sq.h / 2) && inter->coord[1] >= sq.o.coord[1] - (sq.h / 2))
			count++;
		if (inter->coord[2] <= sq.o.coord[2] + (sq.h / 2) && inter->coord[2] >= sq.o.coord[2] - (sq.h / 2))
			count++;
		if (count != 3)
			t = 1E99;
	}
	else
		t = 1E99;
	return (t);
}
