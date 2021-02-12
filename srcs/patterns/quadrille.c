/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadrille.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 15:23:10 by ndemont           #+#    #+#             */
/*   Updated: 2021/02/12 21:06:18 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "geometry.h"
#include <stdio.h>
#include <math.h>

t_pattern    check_pattern(float w, float h, t_vector a, t_vector b)
{
    t_pattern new;

    new.width = w;
    new.height = h;
    new.a = a;
    new.b = b;
    return (new);
}

t_vector   quadrilles_pattern_color(t_pattern pat, float u, float v)
{
    int sum;

    sum = floor(u * pat.width) + floor(v * pat.height);
    if (sum % 2 == 0)
        return (pat.a);
    else
        return (pat.b);
}

t_vector   gradient_pattern_color(t_pattern pat, float u, float v)
{
	t_vector color;

	(void)u;
	//if (v > 0.5)
	//	v = 1 - v;
	//v = 2 * v;
	color.coord[0] = v * pat.a.coord[0] + (1 - v) * pat.b.coord[0];
    color.coord[1] = v * pat.a.coord[1] + (1 - v) * pat.b.coord[1];
    color.coord[2] = v * pat.a.coord[2] + (1 - v) * pat.b.coord[2];
	color = color_limit(color);
	return (color);
}


t_vector   stripes_pattern_color(t_pattern pat, float u, float v)
{
    int sum;

	(void)v;
    sum = floor(u * pat.width);
    if (sum % 2 == 0)
        return (pat.a);
    else
        return (pat.b);
}

t_vector   rings_pattern_color(t_pattern pat, float u, float v)
{
    int sum;

	(void)u;
    sum = floor(v * pat.width);
    if (sum % 2 == 0)
        return (pat.a);
    else
        return (pat.b);
}

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

t_vector	get_sphere_pattern(t_scene *s, int i, t_vector inter)
{
    t_2d coord;
    t_vector color1;
    t_vector color2;
    t_vector color;
    t_vector test;
	float		rot_x;
	float		rot_y;
	float		rot_z;
    t_pattern pat;

    color1 = init_vector(255,0,0);
    color2 = init_vector(0,255,0);
    pat = check_pattern(50, 50, color1, color2);
    rot_x = (inter.coord[0] - s->objects[i].o.coord[0]);
    rot_y = (inter.coord[1] - s->objects[i].o.coord[1]);
    rot_z = (inter.coord[2] - s->objects[i].o.coord[2]);
	test = init_vector(rot_x, rot_y, rot_z);
	coord = spherical_map(test, s, i);
    color = gradient_pattern_color(pat, coord.u, coord.v);
    return (color);
}