/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadrille.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 15:23:10 by ndemont           #+#    #+#             */
/*   Updated: 2021/02/15 12:52:34 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "geometry.h"
#include <stdio.h>
#include <math.h>

int    get_pattern(t_pattern pat, float u, float v, int type, t_vector *color)
{
    t_vector c;

    if (type == 1)
        c = quadrilles_pattern_color(pat, u, v);
    if (type == 2)
        c = stripes_pattern_color(pat, u, v);
    if (type == 3)
        c = rings_pattern_color(pat, u, v);
    if (type == 4)
        c = gradient_pattern_color(pat, u, v);
    if (type != 1 && type != 2 && type != 3 && type != 4)
    {
        printf("Error 20: Wrong pattern type\n");
        return (0);
    }
    *color = c;
    return (1);
}

t_pattern    check_pattern(float w, float h, t_vector a, t_vector b)
{
    t_pattern new;

    new.width = w;
    new.height = h;
    new.a = a;
    new.b = b;
    return (new);
}

void	get_sphere_pattern(t_scene *s, int i, t_vector inter, t_vector *color)
{
    t_2d coord;
    t_vector test;
	float		rot_x;
	float		rot_y;
	float		rot_z;
    t_pattern pat;

    printf("color1 = %f/%f/%f\n", s->objects[i].t2.coord[0], s->objects[i].t2.coord[1], s->objects[i].t2.coord[2]);
    printf("color2 = %f/%f/%f\n", s->objects[i].t1.coord[0], s->objects[i].t1.coord[1], s->objects[i].t1.coord[2]);
    pat = check_pattern(15, 15, s->objects[i].t2, s->objects[i].t1);
    rot_x = (inter.coord[0] - s->objects[i].o.coord[0]);
    rot_y = (inter.coord[1] - s->objects[i].o.coord[1]);
    rot_z = (inter.coord[2] - s->objects[i].o.coord[2]);
	test = init_vector(rot_x, rot_y, rot_z);
	coord = spherical_map(test, s, i);
    if (!(get_pattern(pat, coord.u, coord.v, s->objects[i].h, color)))
    {
        free_scene(0, s);
        exit(1);
    }
    printf("color = %f/%f/%f\n", color->coord[0], color->coord[1], color->coord[2]);
    write(1, "OH NO\n", 6);
}