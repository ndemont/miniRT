/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:16:00 by ndemont           #+#    #+#             */
/*   Updated: 2021/01/27 11:16:28 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <geometry.h>

float		inter_sp(t_ray ray, t_object sp, t_vector *inter, t_vector *normal)
{
	float		b;
	float		c;
	float		t;
	float		t1;
	float		t2;

	t = 1E99;
	b = 2 * scalaire(ray.d, v_minus_v(ray.o, sp.o));
	c = get_norme_2(v_minus_v(ray.o, sp.o)) - (sp.diam * sp.diam);
	if (quadratic_equation(1, b, c, &t1, &t2))
	{
		if (t1 > 0)
			t = t1;
		else
			t = t2;
		*inter = v_plus_v(ray.o, v_mult_i(ray.d, t));
		*normal = get_normalized(v_minus_v(*inter, sp.o));
	}
	return (t);
}
