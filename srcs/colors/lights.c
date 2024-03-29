/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 15:36:39 by ndemont           #+#    #+#             */
/*   Updated: 2021/02/15 18:43:43 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float		intensity_limit(float i)
{
	if (i < 0)
		i = 0;
	if (i > 1)
		i = 1;
	return (i);
}

t_vector	color_limit(t_vector v)
{
	if (v.coord[0] > 255)
		v.coord[0] = 255;
	if (v.coord[1] > 255)
		v.coord[1] = 255;
	if (v.coord[2] > 255)
		v.coord[2] = 255;
	return (v);
}

t_vector	find_intensity(t_vector inter, float *fint, t_vector n, t_scene s)
{
	int			i;
	float		intensity;
	t_vector	new;
	t_vector	rgb;

	i = 0;
	rgb = init_vector(0, 0, 0);
	while (s.lights[i].i != -1)
	{
		new = get_normalized(v_minus_v(s.lights[i].o, inter));
		intensity = (s.lights[i].i * 1000 * scalaire(new, n));
		intensity /= (get_norme_2(v_minus_v(s.lights[i].o, inter)));
		intensity = intensity_limit(intensity);
		intensity *= (check_shadow(&s, inter, n, i));
		*fint += intensity;
		rgb = v_plus_v(rgb, v_mult_i(s.lights[i].c, intensity));
		i++;
	}
	*fint += s.a.i;
	rgb = v_plus_v(rgb, v_mult_i(s.a.color, s.a.i));
	rgb = color_limit(rgb);
	*fint = intensity_limit(*fint);
	return (rgb);
}

t_pixel		fill_pixel(t_scene *s, int obj, t_vector light, float i)
{
	t_pixel		pixel;
	t_vector	color;

	color.coord[0] = fmin(s->objects[obj].c.coord[0], light.coord[0]) * i;
	color.coord[1] = fmin(s->objects[obj].c.coord[1], light.coord[1]) * i;
	color.coord[2] = fmin(s->objects[obj].c.coord[2], light.coord[2]) * i;
	color = apply_filter(color, light, i, s->filter);
	pixel.r = color.coord[0];
	pixel.g = color.coord[1];
	pixel.b = color.coord[2];
	return (pixel);
}

t_pixel		find_color(t_scene *s, int obj, t_vector inter, t_vector normal)
{
	float			intensity;
	t_vector		lights;
	t_vector		new;
	t_pixel			pixel;

	intensity = 0;
	new = v_minus_v(s->lights[0].o, inter);
	new = get_normalized(new);
	lights = find_intensity(inter, &intensity, normal, *s);
	pixel = fill_pixel(s, obj, lights, intensity);
	return (pixel);
}
