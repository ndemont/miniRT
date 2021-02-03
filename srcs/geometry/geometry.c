/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 14:32:23 by ndemont           #+#    #+#             */
/*   Updated: 2021/02/03 11:27:27 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <geometry.h>

float		quadratic_resolution(float a, float b, float c, float *t1, float *t2)
{
		float delta;

		delta = (b * b) - (4 * a * c);
		if (delta < 0)
			return (0);
		*t1 = (-b - (sqrt(delta))) / (2 * a);
		*t2 = (-b + (sqrt(delta))) / (2 * a);
		if (*t2 >= 0)
			return (1);
		else
			return (0);
}

float		scalaire(t_vector v1, t_vector v2)
{
	float rslt;

	rslt = (v1.coord[0] * v2.coord[0]) + (v1.coord[1] * v2.coord[1]) + (v1.coord[2] * v2.coord[2]);
	return (rslt);
}

t_vector	init_vector(float x, float y, float z)
{
	t_vector new;

	new.coord[0] = x;
	new.coord[1] = y;
	new.coord[2] = z;
	return (new);
}

float		get_norme_2(t_vector v)
{
	float rslt;

	rslt = powf(v.coord[0], 2) + powf(v.coord[1], 2) + powf(v.coord[2], 2);
	return (rslt);
}

float		get_norme(t_vector v)
{
	float rslt;

	rslt = powf(v.coord[0], 2) + powf(v.coord[1], 2) + powf(v.coord[2], 2);
	if (!rslt)
		rslt = 0;
	return (rslt);
}

void		normalize(t_vector *v)
{
	float	norm;

	norm = sqrt(get_norme_2(*v));
	v->coord[0] = v->coord[0] / norm;
	v->coord[1] = v->coord[1] / norm;
	v->coord[2] = v->coord[2] / norm;
}

t_vector	get_normalized(t_vector v)
{
	normalize(&v);
	return (v);
}

void	set_plan(t_scene *s)
{
	t_ray		ray;
	float		scal;
	t_vector	normal;
	int 		i;

	i = 0;
	printf("quoi\n");
	while (s->objects[i].type != -1)
	{
		ray.o = s->cameras[s->cam_i].o;
		ray.d = s->cameras[s->cam_i].c;
		normalize(&ray.d);
		if (s->objects[i].type == 5 || s->objects[i].type == 8)
		{
			normal = get_normalized(s->objects[i].d);
			scal = scalaire(v_minus_v(s->objects[i].o, ray.o), normal);
			if (scal > 0)
				s->objects[i].d = v_mult_i(s->objects[i].d, -1);
		}
		if (s->objects[i].type == 7)
		{
			normal = v_produit_v(v_minus_v(s->objects[i].t2, s->objects[i].t1), v_minus_v(s->objects[i].t3, s->objects[i].t1));
			scal = scalaire(v_minus_v(s->objects[i].t1, ray.o), normal);
			s->objects[i].d = normal;
			if (scal > 0)
				s->objects[i].d = v_mult_i(s->objects[i].d, -1);
		}
		i++;
	}
	printf("quoi 2\n");
}
