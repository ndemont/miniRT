/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 11:37:47 by ndemont           #+#    #+#             */
/*   Updated: 2021/02/10 15:21:03 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"
#include "geometry.h"

static void	create_img(t_ray ray, int i[2], t_scene *s, t_matrix m)
{
	t_pixel		pxl;
	t_vector	inter;
	t_vector	normal;
	int			object;

	ray.d.coord[0] = (i[1] - ((s->R[0]) / 2));
	ray.d.coord[1] = (i[0] - ((s->R[1]) / 2));
	normalize(&ray.d);
	ray.d = get_normalized(v_mult_m(ray.d, m));
	object = closest_inter(ray, s, &inter, &normal);
	if (object != -1)
	{
		pxl = find_color(s, object, inter, normal);
		pxl.p = (((s->R[1]) - i[0] - 1) * s->size) + ((s->R[0]) - i[1] - 1) * 4;
		s->data_addr[pxl.p + 2] = pxl.r;
		s->data_addr[pxl.p + 1] = pxl.g;
		s->data_addr[pxl.p + 0] = pxl.b;
	}
}

void		minirt(t_scene *s)
{
	int			i[2];
	t_ray		ray;
	t_matrix	m;

	ray.o = s->cameras[s->cam_i].o;
	ray.d.coord[2] = -((s->R[0]) / (2 * (tan(s->cameras[s->cam_i].f / 2))));
	i[0] = 0;
	m = rotation_matrix(*s);
	while (i[0] < s->R[1])
	{
		i[1] = 0;
		while (i[1] < s->R[0])
		{
			create_img(ray, i, s, m);
			(i[1])++;
		}
		(i[0])++;
	}
}

#ifdef LINUX

void		init_general(t_scene *s)
{
	int x;
	int y;

	(void)x;
	(void)y;
	s->mlx_ptr = mlx_init();
	s->bits_per_pixel = 0;
	s->size = 0;
	s->endian = 0;
	s->lights = 0;
	s->cameras = 0;
	s->objects = 0;
	mlx_get_screen_size(s->mlx_ptr, &x, &y);
	if (s->R[0] > x)
		s->R[0] = x;
	if (s->R[1] > y)
		s->R[1] = y;
}

#else

void		init_general(t_scene *s)
{
	s->mlx_ptr = mlx_init();
	s->bits_per_pixel = 0;
	s->size = 0;
	s->endian = 0;
	s->lights = 0;
	s->cameras = 0;
	s->objects = 0;
	s->R[0] = 0;
	s->R[1] = 0;
}

#endif

int			main(int ac, char **av)
{
	t_scene			s;

	init_general(&s);
	if (check_errors(ac, av, &s))
		return (1);
	init_images(&s);
	if (!mlx_hook(s.win_ptr, 2, 1L << 0, ft_event, &s))
		return (0);
	if (!mlx_hook(s.win_ptr, 17, 1L << 17, ft_cross, &s))
		return (0);
	//if (!mlx_hook(s.win_ptr, 33, 1L << 5, ft_cross, &s))
	//	return (0);
	mlx_loop_hook(s.mlx_ptr, ft_event, &s);
	//if (!mlx_hook(s.win_ptr, 25, 1L << 18, ft_event, &s))
	//	return (0);
	//mlx_loop_hook(s.mlx_ptr, ft_cross, &s);
	print_window(s.mlx_ptr, s.win_ptr, s.images[0].img_ptr);
	return (free_scene(0, &s));
}
