/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 15:36:39 by ndemont           #+#    #+#             */
/*   Updated: 2021/01/27 15:54:30 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	*fint += s.A.i;
	rgb = v_plus_v(rgb, v_mult_i(s.A.color, s.A.i));
	rgb = color_limit(rgb);
	*fint = intensity_limit(*fint);
	return (rgb);
}
