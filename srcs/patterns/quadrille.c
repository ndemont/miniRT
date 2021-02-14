/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadrille.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 15:23:10 by ndemont           #+#    #+#             */
/*   Updated: 2021/02/13 14:40:34 by ndemont          ###   ########.fr       */
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

    color1 = init_vector(255,255,255);
    color2 = init_vector(0,0,0);
    pat = check_pattern(15, 15, color1, color2);
    rot_x = (inter.coord[0] - s->objects[i].o.coord[0]);
    rot_y = (inter.coord[1] - s->objects[i].o.coord[1]);
    rot_z = (inter.coord[2] - s->objects[i].o.coord[2]);
	test = init_vector(rot_x, rot_y, rot_z);
	coord = spherical_map(test, s, i);
    color = quadrilles_pattern_color(pat, coord.u, coord.v);
    return (color);
}

//t_vector	get_sphere_pattern(t_scene *s, int i, t_vector inter)
//{
//    t_2d coord;
//    t_vector color1;
//    t_vector color2;
//    t_vector color;
//    t_pattern pat;
//	t_vector test;
//	float		rot_x;
//	float		rot_y;
//	float		rot_z;

//	(void)test;
//	(void)rot_x;
//	(void)rot_y;
//	(void)rot_z;
//    color1 = init_vector(255,0,0);
//    color2 = init_vector(0,255,0);
//    pat = check_pattern(2, 2, color1, color2);
//    rot_x = (inter.coord[0] - (inter.coord[1] * s->objects[i].d.coord[0]));
//    rot_y = (inter.coord[1] - 0);
//    rot_z = (inter.coord[2] - (inter.coord[1] * s->objects[i].d.coord[2]));
//	test = init_vector(rot_x, rot_y, rot_z);
//	coord = plan_map(test, s, i);
//    color = gradient_pattern_color(pat, coord.u, coord.v);
//    return (color);
//}