/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 12:45:47 by ndemont           #+#    #+#             */
/*   Updated: 2021/02/15 19:09:25 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			get_pattern(t_pattern pat, t_2d coord, int type, t_vector *color)
{
	t_vector c;

	if (type == 1)
		c = quadrilles_pattern_color(pat, coord.u, coord.v);
	if (type == 2)
		c = stripes_pattern_color(pat, coord.u, coord.v);
	if (type == 3)
		c = rings_pattern_color(pat, coord.u, coord.v);
	if (type == 4)
		c = gradient_pattern_color(pat, coord.u, coord.v);
	if (type != 1 && type != 2 && type != 3 && type != 4)
	{
		printf("Error 20: Wrong pattern type\n");
		return (0);
	}
	*color = c;
	return (1);
}

t_pattern	check_pattern(float w, float h, t_vector a, t_vector b)
{
	t_pattern new;

	new.width = w;
	new.height = h;
	new.a = a;
	new.b = b;
	return (new);
}

void		get_sphere_pattern(t_scene *s, int i, t_vector inter, t_vector *rgb)
{
	t_2d		coord;
	t_vector	origin;
	t_vector	rot;
	t_pattern	pat;

	pat = check_pattern(15, 15, s->objects[i].t2, s->objects[i].t1);
	rot.coord[0] = (inter.coord[0] - s->objects[i].o.coord[0]);
	rot.coord[1] = (inter.coord[1] - s->objects[i].o.coord[1]);
	rot.coord[2] = (inter.coord[2] - s->objects[i].o.coord[2]);
	origin = init_vector(rot.coord[0], rot.coord[1], rot.coord[2]);
	coord = spherical_map(origin, s, i);
	if (!(get_pattern(pat, coord, s->objects[i].h, rgb)))
	{
		free_scene(0, s);
		exit(1);
	}
}

t_2d		spherical_map(t_vector inter, t_scene *s, int i)
{
	float	theta;
	float	radius;
	float	phi;
	t_2d	coord;

	theta = atan2(inter.coord[0], inter.coord[2]);
	radius = s->objects[i].diam;
	phi = (inter.coord[1]) / radius;
	phi = acosf(phi);
	coord.u = 1 - ((theta / (2 * M_PI)) + 0.5);
	coord.v = 1 - phi / M_PI;
	return (coord);
}
