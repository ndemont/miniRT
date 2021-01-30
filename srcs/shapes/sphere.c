/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:16:00 by ndemont           #+#    #+#             */
/*   Updated: 2021/01/29 19:56:09 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <geometry.h>

float		quadratic_sp(t_ray ray, t_object sp, float *t1, float *t2)
{
	float		quadratic[3];

	quadratic[0] = 1;
	quadratic[1] = 2 * scalaire(ray.d, v_minus_v(ray.o, sp.o));
	quadratic[2] = get_norme_2(v_minus_v(ray.o, sp.o)) - (sp.diam * sp.diam);
	if (quadratic_resolution(quadratic[0], quadratic[1], quadratic[2], t1, t2))
		return (1);
	else
		return (0);
}

float		inter_sp(t_ray ray, t_object sp, t_vector *inter, t_vector *normal)
{
	float		t;
	float		t1;
	float		t2;

	if (quadratic_sp(ray, sp, &t1, &t2))
	{
		if (t1 > 0)
			t = t1;
		else
			t = t2;
		*inter = v_plus_v(ray.o, v_mult_i(ray.d, t));
		*normal = get_normalized(v_minus_v(*inter, sp.o));
		return (t);
	}
	return (1E99);
}
