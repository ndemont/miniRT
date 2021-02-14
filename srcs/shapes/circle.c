/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:12:46 by ndemont           #+#    #+#             */
/*   Updated: 2021/02/14 21:35:16 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <geometry.h>

float		inter_cl(t_ray ray, t_object cl, t_vector *inter, t_vector *normal)
{
	float		t;
	t_vector	v;
	int			count;
	float		R2;
	float		P1;

	*normal = get_normalized(cl.d);
	count = 0;
	v = v_minus_v(cl.o, ray.o);
	t = scalaire(v, *normal) / scalaire(ray.d, *normal);
	if (t >= 0)
	{
		R2 = cl.diam * cl.diam;
		*inter = v_plus_v(ray.o, v_mult_i(ray.d, t));
		P1 = powf((inter->coord[0] - cl.o.coord[0]), 2);
		P1 = P1 + powf((inter->coord[1] - cl.o.coord[1]), 2);
		P1 = P1 + powf((inter->coord[2] - cl.o.coord[2]), 2);
		if (P1 < R2)
			count++;
	}
	if (count == 0)
		t = 1E99;
	return (t);
}
