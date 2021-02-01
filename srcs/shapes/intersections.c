/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 14:30:04 by ndemont           #+#    #+#             */
/*   Updated: 2021/02/01 19:01:30 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <geometry.h>

float	inter_type(t_ray ray, t_object o, t_vector *inter, t_vector *normal)
{
	float	(*type[13])(t_ray, t_object, t_vector *, t_vector *);
	float	t;

	type[4] = &inter_sp;
	type[6] = &inter_sq;
	type[8] = &inter_cy;
	type[10] = &inter_tr;
	type[12] = &inter_pl;
	t = (*type[o.type])(ray, o, inter, normal);
	return (t);
}

int		closest_inter(t_ray ray, t_scene *s, t_vector *inter, t_vector *normal)
{
	t_vector	inter_p;
	t_vector	normal_p;
	int			i;
	int			object;
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
	return (object);
}
