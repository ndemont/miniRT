/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 12:45:34 by ndemont           #+#    #+#             */
/*   Updated: 2021/02/15 19:01:04 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	quadrilles_pattern_color(t_pattern pat, float u, float v)
{
	int			sum;
	t_vector	color;

	sum = floor(u * pat.width) + floor(v * pat.height);
	color = pat.b;
	if (sum % 2 == 0)
		color = pat.a;
	return (color);
}

t_vector	gradient_pattern_color(t_pattern pat, float u, float v)
{
	t_vector	color;

	(void)u;
	color.coord[0] = v * pat.a.coord[0] + (1 - v) * pat.b.coord[0];
	color.coord[1] = v * pat.a.coord[1] + (1 - v) * pat.b.coord[1];
	color.coord[2] = v * pat.a.coord[2] + (1 - v) * pat.b.coord[2];
	color = color_limit(color);
	return (color);
}

t_vector	stripes_pattern_color(t_pattern pat, float u, float v)
{
	int			sum;
	t_vector	color;

	(void)v;
	sum = floor(u * pat.width);
	color = pat.b;
	if (sum % 2 == 0)
		color = pat.a;
	return (color);
}

t_vector	rings_pattern_color(t_pattern pat, float u, float v)
{
	int			sum;
	t_vector	color;

	(void)u;
	sum = floor(v * pat.width);
	color = pat.b;
	if (sum % 2 == 0)
		color = pat.a;
	return (color);
}
