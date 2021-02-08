/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 10:12:22 by ndemont           #+#    #+#             */
/*   Updated: 2021/02/08 12:19:34 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <mlx.h>

int		ft_cross(int keycode, t_scene *s)
{
	(void)keycode;
	(void)s;
	exit(0);
}

int		ft_event(int keycode, t_scene *s)
{
	if (!ft_close_win(keycode, s))
		exit(0);
	ft_switch_cam(keycode, s);
	ft_move_cam(keycode, s);
	return (1);
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

int		ft_switch_cam(int keycode, t_scene *s)
{
	if (keycode == SWITCH_CAM)
	{
		s->cam_i++;
		if (s->cameras[s->cam_i].f == -1)
			s->cam_i = 0;
		print_window(s->mlx_ptr, s->win_ptr, s->images[s->cam_i].img_ptr);
	}
	return (1);
}

int		ft_move_cam(int keycode, t_scene *s)
{
	t_img	image;
	
	if (keycode == MOVE_L)
	{
		s->cameras[s->cam_i].o.coord[0] = s->cameras[s->cam_i].o.coord[0] + 5;
		image = ft_new_img(s, s->cam_i);
		print_window(s->mlx_ptr, s->win_ptr, image.img_ptr);
	}
	if (keycode == MOVE_R)
	{
		s->cameras[s->cam_i].o.coord[0] = s->cameras[s->cam_i].o.coord[0] - 5;
		image = ft_new_img(s, s->cam_i);
		print_window(s->mlx_ptr, s->win_ptr, image.img_ptr);
	}
	if (keycode == MOVE_F)
	{
		s->cameras[s->cam_i].o.coord[2] = s->cameras[s->cam_i].o.coord[2] + 5;
		image = ft_new_img(s, s->cam_i);
		print_window(s->mlx_ptr, s->win_ptr, image.img_ptr);
	}
	if (keycode == MOVE_B)
	{
		s->cameras[s->cam_i].o.coord[2] = s->cameras[s->cam_i].o.coord[2] - 5;
		image = ft_new_img(s, s->cam_i);
		print_window(s->mlx_ptr, s->win_ptr, image.img_ptr);
	}
	if (keycode == LOOK_L)
	{
		printf("left arrow");
		s->cameras[s->cam_i].c.coord[0] = s->cameras[s->cam_i].c.coord[0] + 0.1;
		if (s->cameras[s->cam_i].c.coord[0] > 1)
			s->cameras[s->cam_i].c.coord[0] = 1;
		image = ft_new_img(s, s->cam_i);
		print_window(s->mlx_ptr, s->win_ptr, image.img_ptr);
	}
	if (keycode == LOOK_R)
	{
		s->cameras[s->cam_i].c.coord[0] = s->cameras[s->cam_i].c.coord[0] - 0.1;
		if (s->cameras[s->cam_i].c.coord[0] < -1)
			s->cameras[s->cam_i].c.coord[0] = -1;
		image = ft_new_img(s, s->cam_i);
		print_window(s->mlx_ptr, s->win_ptr, image.img_ptr);
	}
	if (keycode == LOOK_U)
	{
		s->cameras[s->cam_i].c.coord[1] = s->cameras[s->cam_i].c.coord[1] + 0.1;
		if (s->cameras[s->cam_i].c.coord[1] > 1)
			s->cameras[s->cam_i].c.coord[1] = 1;
		image = ft_new_img(s, s->cam_i);
		print_window(s->mlx_ptr, s->win_ptr, image.img_ptr);
	}
	if (keycode == LOOK_D)
	{
		s->cameras[s->cam_i].c.coord[2] = s->cameras[s->cam_i].c.coord[2] - 0.1;
		if (s->cameras[s->cam_i].c.coord[1] < -1)
			s->cameras[s->cam_i].c.coord[1] = -1;
		image = ft_new_img(s, s->cam_i);
		print_window(s->mlx_ptr, s->win_ptr, image.img_ptr);
	}
	return (1);
}
