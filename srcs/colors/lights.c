/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 15:36:39 by ndemont           #+#    #+#             */
/*   Updated: 2021/02/12 17:52:28 by ndemont          ###   ########.fr       */
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
		//s.lights[i].c = init_vector(190, 110, 50); // sepia
		rgb = v_plus_v(rgb, v_mult_i(s.lights[i].c, intensity));
		i++;
	}
	*fint += s.a.i;
	//s.a.color = init_vector(190, 110, 50); sepia
	rgb = v_plus_v(rgb, v_mult_i(s.a.color, s.a.i));
	rgb = color_limit(rgb);
	*fint = intensity_limit(*fint);
	return (rgb);
}

t_pixel		fill_pixel(t_scene *s, int obj, t_vector light, float intensity)
{
	t_pixel pixel;

	//s->objects[obj].c = init_vector(255,255,255); sepia
	pixel.r = fmin(s->objects[obj].c.coord[0], light.coord[0]) * intensity;
	pixel.g = fmin(s->objects[obj].c.coord[1], light.coord[1]) * intensity;
	pixel.b = fmin(s->objects[obj].c.coord[2], light.coord[2]) * intensity;
	// pixel.r = 255 - pixel.r;
	// pixel.g = 255 - pixel.g;
	// pixel.b = 255 - pixel.b; negative;
	// pixel.g = 0; // rouge
	// pixel.b = 0; //rouge;
	//pixel.r = 0; //beuleu
	//pixel.g = 0; // bleu 
	//pixel.r = 0; // vert
	//pixel.b = 0; // vert
	// pixel.r = (fmin(s->objects[obj].c.coord[0], light.coord[0]) + fmin(s->objects[obj].c.coord[1], light.coord[1]) + fmin(s->objects[obj].c.coord[2], light.coord[2])) / 3 * intensity;
	// pixel.g = pixel.r;
	// pixel.b = pixel.r; b and white
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
