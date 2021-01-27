/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:12:58 by ndemont           #+#    #+#             */
/*   Updated: 2021/01/27 11:13:00 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <geometry.h>

float		inter_cy(t_ray ray, t_object cy, t_vector *inter, t_vector *N)
{
	float 		r;
	float		t;
	t_vector 	va;
	t_vector	v;
	t_vector	rao;
	t_vector 	s;
	t_vector	rorcy;
	float		D;
	float		t1;
	float		t2;
	float		a;
	float		b;
	float		c;
	t_vector	C;
	float		d;

	r = cy.diam / 2;
	t = -1;
	v = ray.d;
	t2 = 0;
	s = get_normalized(cy.d);
	rorcy = v_minus_v(ray.o, cy.o);
	rao = v_produit_v(v_produit_v(s, rorcy), s);
	va = v_produit_v(v_produit_v(s, v), s);
	a = scalaire(va, va);
	b = scalaire(v_mult_i(rao, 2), va);
	c = scalaire(rao, rao) - powf(r, 2);
	D = (b * b) - (4 * a * c);
	if (D >= 0)
	{
		t1 = (-b - (sqrt(D))) / (2 * a);
		t2 = (-b + (sqrt(D))) / (2 * a);
 		if (t2 >= 0)
		{
			if (t1 > 0)
			{
				t = t1;
				inter->coord[0] = ray.o.coord[0] + (t * ray.d.coord[0]);
				inter->coord[1] = ray.o.coord[1] + (t * ray.d.coord[1]);
				inter->coord[2] = ray.o.coord[2] + (t * ray.d.coord[2]);
				d = scalaire(v_minus_v(*inter, cy.o), s);
				if (d < cy.h / 2 && d > -cy.h / 2)
				{
		


					C = v_plus_v(cy.o, v_mult_i(s, d));
					*N = get_normalized(v_minus_v(*inter, C));
				}
				else 
					t = -1;
			}
			if (t == -1)
			{
				t = t2;
				inter->coord[0] = ray.o.coord[0] + (t * ray.d.coord[0]);
				inter->coord[1] = ray.o.coord[1] + (t * ray.d.coord[1]);
				inter->coord[2] = ray.o.coord[2] + (t * ray.d.coord[2]);
				d = scalaire(v_minus_v(*inter, cy.o), s);
				if (d < cy.h / 2 && d > -cy.h / 2)
				{
					C = v_plus_v(cy.o, v_mult_i(s, d));
					*N = get_normalized(v_minus_v(*inter, C));

				}
				else
					t = -1;
			}
		}
	}
	if (t == -1)
		t = 1E99;
	if (scalaire(*N, ray.d) > 0)
		*N = v_mult_i(*N, -1);
	return (t);
}