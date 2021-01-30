/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 10:12:22 by ndemont           #+#    #+#             */
/*   Updated: 2021/01/30 13:19:24 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <mlx.h>

int             ft_event(int keycode, t_scene *s)
{
    if (!ft_close_win(keycode, s))
		exit (0);
    ft_switch_cam(keycode, s);
    return (1);
}

int             ft_close_win(int keycode, t_scene *s)
{
	if (keycode == 0x35)
	{
		mlx_destroy_window(s->mlx_ptr, s->win_ptr);
		return (0);
	}
	return (1);
}

int             ft_switch_cam(int keycode, t_scene *s)
{
    if (keycode == 0x08)
    {
        s->cam_i++;
        if (s->cameras[s->cam_i].f == -1)
            s->cam_i = 0;
        //color_img(s);
	    //mlx_clear_window(s->mlx_ptr, s->win_ptr);
        print_window(s->mlx_ptr, s->win_ptr, s->images[s->cam_i].img_ptr);
    }
    return (1);
}