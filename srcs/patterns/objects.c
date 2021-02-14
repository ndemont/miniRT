/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 12:45:47 by ndemont           #+#    #+#             */
/*   Updated: 2021/02/13 14:09:15 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_2d    spherical_map(t_vector inter, t_scene *s, int i)
{
    float   theta;
    float   radius;
    float   phi;
    float   raw_u;
    float   u;
    float   v;
    t_2d    coord;

	//inter = init_vector(fabs(inter.coord[0]), fabs(inter.coord[1]), fabs(inter.coord[2]));
    theta = atan2(inter.coord[0], inter.coord[2]);
    radius = s->objects[i].diam;
    phi = (inter.coord[1]) / radius;
	phi = acosf(phi);
    raw_u = theta / (2 * M_PI);
    u = 1 - (raw_u + 0.5);
    v = 1 - phi / M_PI;
    coord.u = u;
    coord.v = v;
    return (coord);
}

t_2d    plan_map(t_vector inter, t_scene *s, int i)
{
    float   u;
    float   v;
	float	x;
	float	y;
    t_2d    coord;

	(void)s;
	(void)i;
    u = modff(inter.coord[0], &x);
    v = modff(inter.coord[2], &y);
	//printf("coord x = %f\ncoord z = %f\n", inter.coord[0], inter.coord[2]);
	//printf("x = %f\ny = %f\n", x, y);
	//printf("u = %f\nv = %f\n", u, v);
    coord.u = u;
    coord.v = v;
    return (coord);
}