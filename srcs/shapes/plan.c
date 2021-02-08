/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:12:28 by ndemont           #+#    #+#             */
/*   Updated: 2021/02/08 10:15:03 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <geometry.h>

float		inter_pl(t_ray ray, t_object sq, t_vector *inter, t_vector *n)
{
	float		t;
	t_vector	v;

	*n = sq.d;
	*n = get_normalized(*n);
	v = v_minus_v(sq.o, ray.o);
	t = scalaire(v, *n) / scalaire(ray.d, *n);
	if (t >= 0.000001)
		*inter = v_plus_v(ray.o, v_mult_i(ray.d, t));
	else
		t = 1E99;
	return (t);
}
