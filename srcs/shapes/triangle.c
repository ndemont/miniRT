/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:12:37 by ndemont           #+#    #+#             */
/*   Updated: 2021/01/27 11:12:40 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <geometry.h>

float		inter_tr(t_ray ray, t_object sp, t_vector *inter, t_vector *N)
{
	float		a;
	float		t;
	float		tf;
	int			i;
	int			final;
	t_vector	v1;
	t_vector	v2;
	t_vector	v5;
	float		v3;
	float		v4;
	t_vector 	u;
	t_vector 	v;
	t_vector 	w;
	double		m11;
	double		m12;
	double		m22;
	double		detm;
	double		b11;
	double		b21;
	double		beta;
	double		detb;
	double		g12;
	double		g22;
	double		detg;
	double		gamma;
	double		alpha;

	i = 0;
	a = 1;
	tf = 1E99;
	final = -1;
	v1 = v_minus_v(sp.d, sp.o);
	v2 = v_minus_v(sp.p, sp.o);
	*N = v_produit_v(v1, v2);
	*N = get_normalized(*N);
	//*N = get_normalized(sp.d);
	//printf("normal = %f/%f/%f\n", N->coord[0], N->coord[1], N->coord[2]);
	v5 = v_minus_v(sp.p, ray.o);
	v3 = scalaire(v5, *N);
	v4 = scalaire(ray.d, *N);
	t = v3 / v4;
	//write(1, "test 00\n", 9);
	if (t >= 0)
	{
		inter->coord[0] = ray.o.coord[0] + (t * ray.d.coord[0]);
		inter->coord[1] = ray.o.coord[1] + (t * ray.d.coord[1]);
		inter->coord[2] = ray.o.coord[2] + (t * ray.d.coord[2]);
		u = v_minus_v(sp.d, sp.o);
		v = v_minus_v(sp.p, sp.o);
		w = v_minus_v(*inter, sp.o);
		// u = v_minus_v(sp.p1, sp.p2);
		// v = v_minus_v(sp.p3, sp.p2);
		// w = v_minus_v(*inter, sp.p2);
		m11 = get_norme_2(u);
		m12 = scalaire(u, v);
		m22 = get_norme_2(v);
		detm = (m11) * (m22) - (m12 * m12);
		b11 = scalaire(w, u);
		b21 = scalaire(w, v);
		detb = (b11) * (m22) - (b21 * m12);
		beta = detb / detm;
		g12 = b11;
		g22 = b21;
		detg = (m11 * g22) - (m12 * g12);
		gamma = detg / detm;
		alpha = 1 - beta - gamma;
		if (alpha >= 0 && alpha <= 1 && beta >= 0 && beta <= 1 && gamma >= 0 && gamma <= 1)
			tf = t;
	}
	return (tf);
}