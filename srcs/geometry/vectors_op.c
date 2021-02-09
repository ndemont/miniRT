/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 14:09:13 by ndemont           #+#    #+#             */
/*   Updated: 2021/02/09 15:25:46 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include "geometry.h"

t_vector	v_plus_v(t_vector v1, t_vector v2)
{
	t_vector v3;

	v3.coord[0] = v1.coord[0] + v2.coord[0];
	v3.coord[1] = v1.coord[1] + v2.coord[1];
	v3.coord[2] = v1.coord[2] + v2.coord[2];
	return (v3);
}

t_vector	v_minus_v(t_vector v1, t_vector v2)
{
	t_vector v3;

	v3.coord[0] = v1.coord[0] - v2.coord[0];
	v3.coord[1] = v1.coord[1] - v2.coord[1];
	v3.coord[2] = v1.coord[2] - v2.coord[2];
	return (v3);
}

t_vector	v_mult_v(t_vector v1, t_vector v2)
{
	t_vector v3;

	v3.coord[0] = v1.coord[0] * v2.coord[0];
	v3.coord[1] = v1.coord[1] * v2.coord[1];
	v3.coord[2] = v1.coord[2] * v2.coord[2];
	return (v3);
}

t_vector	v_dot_v(t_vector v1, t_vector v2)
{
	t_vector v3;

	v3.coord[0] = v1.coord[1] * v2.coord[2] - v1.coord[2] * v2.coord[1];
	v3.coord[1] = v1.coord[2] * v2.coord[0] - v1.coord[0] * v2.coord[2];
	v3.coord[2] = v1.coord[0] * v2.coord[1] - v1.coord[1] * v2.coord[0];
	return (v3);
}

t_vector	v_div_v(t_vector v1, t_vector v2)
{
	t_vector v3;

	v3.coord[0] = v1.coord[0] / v2.coord[0];
	v3.coord[1] = v1.coord[1] / v2.coord[1];
	v3.coord[2] = v1.coord[2] / v2.coord[2];
	return (v3);
}
