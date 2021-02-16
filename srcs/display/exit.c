/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 11:23:38 by ndemont           #+#    #+#             */
/*   Updated: 2021/02/15 20:42:11 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"

int		ft_cross(int keycode, t_scene *s)
{
	(void)keycode;
	(void)s;
	exit(0);
}

int		ft_close_win(int keycode, t_scene *s)
{
	(void)s;
	if (keycode == ESC)
		return (0);
	return (1);
}
