/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 14:30:04 by ndemont           #+#    #+#             */
/*   Updated: 2021/02/15 13:00:53 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"
#include "minirt.h"

float	inter_type(t_ray ray, t_object o, t_vector *inter, t_vector *normal)
{
	float	(*type[13])(t_ray, t_object, t_vector *, t_vector *);
	float	t;

	type[4] = &inter_sp;
	type[5] = &inter_sq;
	type[6] = &inter_cy;
	type[7] = &inter_tr;
	type[8] = &inter_pl;
	type[9] = &inter_cl;
	type[10] = &inter_sp;
	t = (*type[o.type])(ray, o, inter, normal);
	return (t);
}

int		near_inter(t_ray ray, t_scene *s, t_vector *inter, t_vector *normal)
{
	t_vector	inter_p;
	t_vector	normal_p;
	int			object;
	int			i;
	float		t[2];

	t[0] = 1E99;
	object = -1;
	i = 0;
	while (s->objects[i].type != -1)
	{
		t[1] = inter_type(ray, s->objects[i], &inter_p, &normal_p);
		if (t[1] < t[0])
		{
			t[0] = t[1];
			*normal = normal_p;
			*inter = inter_p;
			object = i;
		}
		i++;
	}
	if (object != -1 && s->objects[object].type == 10)
		get_sphere_pattern(s, object, *inter, &(s->objects[object].c));
	return (object);
}
