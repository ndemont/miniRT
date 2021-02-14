/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:16:00 by ndemont           #+#    #+#             */
/*   Updated: 2021/02/14 21:34:47 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

float		quadratic_sp(t_ray ray, t_object sp, float t[2])
{
	float		quadratic[3];

	quadratic[0] = 1;
	quadratic[1] = 2 * scalaire(ray.d, v_minus_v(ray.o, sp.o));
	quadratic[2] = get_norme_2(v_minus_v(ray.o, sp.o)) - (sp.diam * sp.diam);
	if (quadratic_resolution(quadratic[0], quadratic[1], quadratic[2], t))
		return (1);
	else
		return (0);
}

float		inter_sp(t_ray ray, t_object sp, t_vector *inter, t_vector *normal)
{
	float		tf;
	float		t[2];

	if (quadratic_sp(ray, sp, t))
	{
		if (t[0] > 0.000001)
			tf = t[0];
		else
			tf = t[1];
		*inter = v_plus_v(ray.o, v_mult_i(ray.d, tf));
		*normal = get_normalized(v_minus_v(*inter, sp.o));
		return (tf);
	}
	return (1E99);
}
