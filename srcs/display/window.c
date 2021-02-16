/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 12:11:34 by ndemont           #+#    #+#             */
/*   Updated: 2021/02/16 12:40:13 by ndemont          ###   ########.fr       */
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

	img.img_ptr = mlx_new_image(s->mlx_ptr, s->r[0], s->r[1]);
	s->data_addr = (unsigned char *)mlx_get_data_addr(img.img_ptr,
		&(s->bits_per_pixel), &(s->size), &(s->endian));
	minirt(s);
	return (img);
}

t_img	*ft_load_imgs(t_scene *s)
{
	int		i;
	t_img	*images;

	i = 0;
	images = malloc(sizeof(t_img) * s->cam_nbr);
	while (i < s->cam_nbr)
	{
		s->cam_i = i;
		images[i] = ft_new_img(s);
		i++;
		ft_printf("Camera number %i created.\n", i);
	}
	return (images);
}

void	init_images(t_scene *s)
{
	set_plan(s);
	s->win_ptr = mlx_new_window(s->mlx_ptr, s->r[0], s->r[1], "miniRT");
	s->images = ft_load_imgs(s);
	s->cam_i = 0;
}
