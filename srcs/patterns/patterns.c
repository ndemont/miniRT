/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 12:45:34 by ndemont           #+#    #+#             */
/*   Updated: 2021/02/14 21:34:47 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	v = floor(v * pat.height);
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