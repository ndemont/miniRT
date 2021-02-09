/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 12:11:34 by ndemont           #+#    #+#             */
/*   Updated: 2021/02/09 15:08:14 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"

void	print_window(void *mlx_ptr, void *win_ptr, void *img_ptr)
{
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
	mlx_loop(mlx_ptr);
}

t_img	ft_new_img(t_scene *s)
{
	t_img img;

	img.img_ptr = mlx_new_image(s->mlx_ptr, s->R[0], s->R[1]);
	s->data_addr = (unsigned char *)mlx_get_data_addr(img.img_ptr,
		&(s->bits_per_pixel), &(s->size), &(s->endian));
	minirt(s);
	return (img);
}

t_img	*ft_load_imgs(t_scene *s)
{
	int 	i;
	t_img	*images;

	i = 0;
	images = malloc(sizeof(t_img) * s->cam_nbr);
	while (i < s->cam_nbr)
	{
		s->cam_i = i;
		images[i] = ft_new_img(s);
		i++;
	}
	return (images);
}

// void	init_general(t_scene *s)
// {
// 	int x;
// 	int y;

// 	(void)x;
// 	(void)y;
// 	printf("initialization");
// 	s->mlx_ptr = mlx_init();
// 	s->bits_per_pixel = 0;
// 	s->size = 0;
// 	s->endian = 0;
// #ifdef LINUX
// 	mlx_get_screen_size(s->mlx_ptr, &x, &y);
// #endif

// 	s->win_ptr = mlx_new_window(s->mlx_ptr, s->R[0], s->R[1], "miniRT");
// 	s->images = ft_load_imgs(s);
// 	s->cam_i = 0;
// }


void	init_general(t_scene *s)
{
	int x;
	int y;

	(void)x;
	(void)y;
	printf("initialization");
	s->mlx_ptr = mlx_init();
	s->bits_per_pixel = 0;
	s->size = 0;
	s->endian = 0;
#ifdef LINUX
	mlx_get_screen_size(s->mlx_ptr, &x, &y);
#endif
	set_plan(s);
	s->win_ptr = mlx_new_window(s->mlx_ptr, s->R[0], s->R[1], "miniRT");
	s->images = ft_load_imgs(s);
	s->cam_i = 0;
}
