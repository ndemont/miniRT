/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 14:32:23 by ndemont           #+#    #+#             */
/*   Updated: 2021/02/10 15:49:17 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"
#include "minirt.h"

float		quadratic_resolution(float a, float b, float c, float t[2])
{
	float delta;

	delta = (b * b) - (4 * a * c);
	if (delta < 0)
		return (0);
	t[0] = (-b - (sqrt(delta))) / (2 * a);
	t[1] = (-b + (sqrt(delta))) / (2 * a);
	if (t[1] >= 0.000001)
		return (1);
	else
		return (0);
}

t_vector	init_vector(float x, float y, float z)
{
	t_vector new;

	new.coord[0] = x;
	new.coord[1] = y;
	new.coord[2] = z;
	return (new);
}

void		switch_normal(t_scene *s, t_ray ray, int i)
{
	float		scal;
	t_vector	normal1;
	t_vector	normal2;
	t_vector	normal3;
	t_vector	normal;

	if (s->objects[i].type == 5 || s->objects[i].type == 8)
	{
		normal = get_normalized(s->objects[i].d);
		scal = scalaire(v_minus_v(s->objects[i].o, ray.o), normal);
		if (scal > 0)
			s->objects[i].d = v_mult_i(s->objects[i].d, -1);
	}
	if (s->objects[i].type == 7)
	{
		printf("Test");
		normal1 = v_minus_v(s->objects[i].t3, s->objects[i].t1);
		printf("ray1 x = %f\n", normal1.coord[0]);
		printf("ray1 y = %f\n", normal1.coord[1]);
		printf("ray1 z = %f\n", normal1.coord[2]);
		normal2 = v_minus_v(s->objects[i].t2, s->objects[i].t1);
		printf("ray2 x = %f\n", normal2.coord[0]);
		printf("ray2 y = %f\n", normal2.coord[1]);
		printf("ray2 z = %f\n", normal2.coord[2]);
		normal3 = v_dot_v(normal1, normal2);
		printf("ray3 x = %f\n", normal3.coord[0]);
		printf("ray3 y = %f\n", normal3.coord[1]);
		printf("ray3 z = %f\n", normal3.coord[2]);
		normal = v_dot_v(v_minus_v(s->objects[i].t2, s->objects[i].t1),
			v_minus_v(s->objects[i].t3, s->objects[i].t1));
		printf("ray x = %f\n", normal.coord[0]);
		printf("ray y = %f\n", normal.coord[1]);
		printf("ray z = %f\n", normal.coord[2]);
		scal = scalaire(v_minus_v(s->objects[i].t1, ray.o), normal);
		s->objects[i].d = normal;
		if (scal > 0)
			s->objects[i].d = v_mult_i(s->objects[i].d, -1);
	}
}

void		set_plan(t_scene *s)
{
	t_ray		ray;
	int			i;

	i = 0;
	while (s->objects[i].type != -1)
	{
		ray.o = s->cameras[s->cam_i].o;
		ray.d = s->cameras[s->cam_i].c;
		normalize(&ray.d);
		switch_normal(s, ray, i);
		i++;
	}
}
