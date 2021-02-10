/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:12:37 by ndemont           #+#    #+#             */
/*   Updated: 2021/02/10 15:58:39 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <geometry.h>

float		cramer_tr(t_object tr, t_vector inter)
{
	double m[3];
	double g[2];
	double alpha;
	double beta;
	double gamma;

	m[0] = get_norme_2(v_minus_v(tr.t2, tr.t1));
	m[1] = scalaire(v_minus_v(tr.t2, tr.t1), v_minus_v(tr.t3, tr.t1));
	m[2] = get_norme_2(v_minus_v(tr.t3, tr.t1));
	g[0] = scalaire(v_minus_v(inter, tr.t1), v_minus_v(tr.t2, tr.t1));
	g[1] = scalaire(v_minus_v(inter, tr.t1), v_minus_v(tr.t3, tr.t1));
	beta = ((g[0] * m[2]) - (g[1] * m[1])) / ((m[0] * m[2]) - (m[1] * m[1]));
	gamma = ((m[0] * g[1]) - (m[1] * g[0])) / ((m[0] * m[2]) - (m[1] * m[1]));
	alpha = 1 - beta - gamma;
	if (alpha >= 0 && alpha <= 1)
		if (beta >= 0 && beta <= 1)
			if (gamma >= 0 && gamma <= 1)
				return (1);
	return (0);
}

float		inter_tr(t_ray ray, t_object tr, t_vector *p, t_vector *normal)
{
	float		t;

	*normal = tr.d;
	*normal = get_normalized(*normal);
	t = scalaire(v_minus_v(tr.t3, ray.o), *normal) / scalaire(ray.d, *normal);
	if (t >= 0)
	{
		*p = v_plus_v(ray.o, v_mult_i(ray.d, t));
		if (cramer_tr(tr, *p))
			return (t);
	}
	return (1E99);
}
