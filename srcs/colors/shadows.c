/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 15:35:41 by ndemont           #+#    #+#             */
/*   Updated: 2021/02/10 18:11:49 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float		check_shadow(t_scene *s, t_vector inter, t_vector normal, int l)
{
	t_ray		ray;
	double		ret;
	float		d;
	int			i;

	i = 0;
	ray.o = v_plus_v(inter, v_mult_i(normal, 0.001));
	ray.d = get_normalized(v_minus_v(s->lights[l].o, ray.o));
	d = get_norme_2(v_minus_v(s->lights[l].o, ray.o));
	while (s->objects[i].type != -1)
	{
		ret = inter_type(ray, s->objects[i], &inter, &normal);
		if (ret < 1E99)
		{
			if (ret * ret < d)
				return (0);
		}
		i++;
	}
	return (1);
}
