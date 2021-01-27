/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:12:58 by ndemont           #+#    #+#             */
/*   Updated: 2021/01/27 14:01:13 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <geometry.h>

float		quadratic_cy(t_ray ray, t_object cy, float *t1, float *t2)
{
	float		quadratic[3];
	t_vector	va;
	t_vector	rao;
	t_vector	rorcy;

	rorcy = v_minus_v(ray.o, cy.o);
	rao = v_produit_v(v_produit_v(cy.d, rorcy), cy.d);
	va = v_produit_v(v_produit_v(cy.d, ray.d), cy.d);
	quadratic[0] = scalaire(va, va);
	quadratic[1] = scalaire(v_mult_i(rao, 2), va);
	quadratic[2] = scalaire(rao, rao) - powf(cy.diam, 2);
	if (quadratic_resolution(quadratic[0], quadratic[1], quadratic[2], t1, t2))
		return (1);
	else
		return (0);
}

float		finite_cy(t_ray ray, t_object cy, float *t, t_vector *inter)
{
	float d;

	if (*t < 0)
		return (0);
	*inter = v_plus_v(ray.o, v_mult_i(ray.d, *t));
	d = scalaire(v_minus_v(*inter, cy.o), cy.d);
	if (d < cy.h / 2 && d > -cy.h / 2)
		return (1);
	return (0);
}

float		inter_cy(t_ray ray, t_object cy, t_vector *inter, t_vector *normal)
{
	float		t;
	float		t1;
	float		t2;
	t_vector	o;
	float		d;

	cy.d = get_normalized(cy.d);
	if (quadratic_cy(ray, cy, &t1, &t2))
	{
		if (finite_cy(ray, cy, &t1, inter))
			t = t1;
		else if (finite_cy(ray, cy, &t2, inter))
			t = t2;
		else
			return (1E99);
		d = scalaire(v_minus_v(*inter, cy.o), cy.d);
		o = v_plus_v(cy.o, v_mult_i(cy.d, d));
		*normal = get_normalized(v_minus_v(*inter, o));
		if (scalaire(*normal, ray.d) > 0)
			*normal = v_mult_i(*normal, -1);
		return (t);
	}
	return (1E99);
}
