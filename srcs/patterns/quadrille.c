/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadrille.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 15:23:10 by ndemont           #+#    #+#             */
/*   Updated: 2021/02/12 16:39:00 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>
#include <math.h>

typedef struct   s_pattern
{
    float width;
    float height;
    t_vector a;
    t_vector b;
}               t_pattern;

typedef struct   s_2d
{
    float u;
    float v;
}               t_2d;

t_pattern    create_pattern(float w, float h, t_vector a, t_vector b)
{
    t_pattern new;

    new.width = w;
    new.height = h;
    new.a = a;
    new.b = b;
    return (new);
}

t_vector   get_pattern_color(t_pattern pat, float u, float v)
{
    int sum;

    sum = floor(u * 2 * pat.width) + floor(v * pat.height);
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

    theta = atan2(inter.coord[0], inter.coord[2]);
    radius = s->objects[i].diam;
    printf("inter.coord[1] = %f\n", inter.coord[1]);
    phi = inter.coord[1] / radius;
    if (phi > 1)
        phi = M_PI;
    else
        phi = acosf(inter.coord[1] / radius);
    printf("phi = %f\n", phi);
    raw_u = theta / (2 * M_PI);
    u = 1 - (raw_u + 0.5);
    v = 1 - phi / M_PI;
    printf("u = %f, v = %f\n", u, v);
    coord.u = u;
    coord.v = v;
    return (coord);
}

t_vector    get_sphere_pattern(t_scene *s, int i, t_vector inter)
{
    t_2d coord;
    t_vector color1;
    t_vector color2;
    t_vector color;
    t_pattern pat;

    color1 = init_vector(200,100,100);
    color2 = init_vector(100,100,200);
    pat = create_pattern(50, 50, color1, color2);
    coord = spherical_map(inter, s, i);
    color = get_pattern_color(pat, coord.u, coord.v);
    printf("color = %f/%f/%f\n", color.coord[0], color.coord[1], color.coord[2]);
    return (color);
}