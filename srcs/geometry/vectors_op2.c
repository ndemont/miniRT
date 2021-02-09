/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_op2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 14:16:40 by ndemont           #+#    #+#             */
/*   Updated: 2021/02/09 11:33:38 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include "geometry.h"

t_vector	v_minus_i(t_vector v, float i)
{
	t_vector v3;

	v3.coord[0] = v.coord[0] - i;
	v3.coord[1] = v.coord[1] - i;
	v3.coord[2] = v.coord[2] - i;
	return (v3);
}

t_vector	v_mult_i(t_vector v, float i)
{
	t_vector v3;

	v3.coord[0] = v.coord[0] * i;
	v3.coord[1] = v.coord[1] * i;
	v3.coord[2] = v.coord[2] * i;
	return (v3);
}

t_vector	v_div_i(t_vector v, float i)
{
	t_vector v3;

	v3.coord[0] = v.coord[0] / i;
	v3.coord[1] = v.coord[1] / i;
	v3.coord[2] = v.coord[2] / i;
	return (v3);
}

t_vector	v_plus_i(t_vector v, float i)
{
	t_vector v3;

	v3.coord[0] = v.coord[0] + i;
	v3.coord[1] = v.coord[1] + i;
	v3.coord[2] = v.coord[2] + i;
	return (v3);
}
