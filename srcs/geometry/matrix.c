/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 11:32:50 by ndemont           #+#    #+#             */
/*   Updated: 2021/02/14 22:55:28 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "geometry.h"

t_vector	v_mult_m(t_vector v, t_matrix m)
{
	t_vector new;

	new.coord[0] = (m.r1.coord[0] * v.coord[0]) + (m.r2.coord[0] * v.coord[1]);
	new.coord[0] = new.coord[0] + (m.r3.coord[0] * v.coord[2]);
	new.coord[1] = (m.r1.coord[1] * v.coord[0]) + (m.r2.coord[1] * v.coord[1]);
	new.coord[1] = new.coord[1] + (m.r3.coord[1] * v.coord[2]);
	new.coord[2] = (m.r1.coord[2] * v.coord[0]) + (m.r2.coord[2] * v.coord[1]);
	new.coord[2] = new.coord[2] + (m.r3.coord[2] * v.coord[2]);
	return (new);
}

t_matrix	rotation_matrix(t_vector c)
{
	t_matrix matrix;
	t_vector forward;
	t_vector right;
	t_vector up;

	forward = get_normalized(v_mult_i(c, -1));
	if ((int)forward.coord[1] == 1 || (int)forward.coord[1] == -1)
		right = get_normalized(init_vector(1, 0, 0));
	else
		right = get_normalized(init_vector(0, 1, 0));
	right = v_dot_v(right, forward);
	up = v_dot_v(forward, right);
	matrix.r1 = right;
	matrix.r2 = up;
	matrix.r3 = forward;
	return (matrix);
}
