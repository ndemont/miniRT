/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 17:18:54 by ndemont           #+#    #+#             */
/*   Updated: 2021/02/15 18:43:06 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	blackandwhite(t_vector color, t_vector light, float intensity)
{
	t_vector new;

	new.coord[0] = fmin(color.coord[0], light.coord[0]);
	new.coord[0] = new.coord[0] + fmin(color.coord[1], light.coord[1]);
	new.coord[0] = new.coord[0] + fmin(color.coord[2], light.coord[2]);
	new.coord[0] = new.coord[0] / 3 * intensity;
	new.coord[1] = new.coord[0];
	new.coord[2] = new.coord[0];
	return (new);
}

t_vector	negative(t_vector color)
{
	t_vector new;

	new.coord[0] = 255 - color.coord[0];
	new.coord[1] = 255 - color.coord[1];
	new.coord[2] = 255 - color.coord[2];
	return (new);
}

t_vector	rgb(t_vector color, int filter)
{
	t_vector new;

	new = init_vector(0, 0, 0);
	if (filter == 3)
		new.coord[0] = color.coord[0];
	else if (filter == 4)
		new.coord[1] = color.coord[1];
	else if (filter == 5)
		new.coord[2] = color.coord[2];
	return (new);
}

t_vector	apply_filter(t_vector color, t_vector light, float i, int filter)
{
	if (filter == 1)
		color = blackandwhite(color, light, i);
	else if (filter == 2)
		color = negative(color);
	else if (filter == 3 || filter == 4 || filter == 5)
		color = rgb(color, filter);
	return (color);
}
