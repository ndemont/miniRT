/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 10:12:22 by ndemont           #+#    #+#             */
/*   Updated: 2021/02/10 12:20:33 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"

int				ft_event(int keycode, t_scene *s)
{
	if (!ft_close_win(keycode, s))
	{
		free_scene(0, s);
		exit(0);
	}
	ft_switch_cam(keycode, s);
	ft_move_cam(keycode, s);
	return (1);
}

int				ft_switch_cam(int keycode, t_scene *s)
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

static void		ft_print_w(t_scene *s)
{
	t_img image;

	image = ft_new_img(s);
	print_window(s->mlx_ptr, s->win_ptr, image.img_ptr);
}

void			ft_move_cam(int keycode, t_scene *s)
{
	if (keycode == MOVE_L)
	{
		s->cameras[s->cam_i].o.coord[0] = s->cameras[s->cam_i].o.coord[0] + 5;
		ft_print_w(s);
	}
	if (keycode == MOVE_R)
	{
		s->cameras[s->cam_i].o.coord[0] = s->cameras[s->cam_i].o.coord[0] - 5;
		ft_print_w(s);
	}
	if (keycode == MOVE_F)
	{
		s->cameras[s->cam_i].o.coord[2] = s->cameras[s->cam_i].o.coord[2] + 5;
		ft_print_w(s);
	}
	if (keycode == MOVE_B)
	{
		s->cameras[s->cam_i].o.coord[2] = s->cameras[s->cam_i].o.coord[2] - 5;
		ft_print_w(s);
	}
}
