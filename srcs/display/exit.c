/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 11:23:38 by ndemont           #+#    #+#             */
/*   Updated: 2021/02/10 18:51:15 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"

int		ft_cross(int keycode, t_scene *s)
{
	(void)keycode;
	free_scene(0, s);
	exit(0);
}

int		ft_close_win(int keycode, t_scene *s)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(s->mlx_ptr, s->win_ptr);
		return (0);
	}
	return (1);
}