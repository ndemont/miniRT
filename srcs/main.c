/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 11:37:47 by ndemont           #+#    #+#             */
/*   Updated: 2021/02/15 12:40:06 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"
#include "geometry.h"

int		init_scene(t_scene *s, char **list)
{
	int c;
	int l;
	int o;

	ft_count_elem(list, &c, &l, &o);
	if (!(s->lights = malloc(sizeof(t_light) * (l + 1))))
		return (0);
	s->lights[0].i = -1;
	if (!(s->cameras = malloc(sizeof(t_camera) * (c + 1))))
		return (0);
	s->cameras[0].f = -1;
	s->cam_nbr = c;
	if (!(s->objects = malloc(sizeof(t_object) * (o + 1))))
		return (0);
	s->objects[0].type = -1;
	s->a.i = 0;
	return (1);
}

void	create_img(t_ray ray, t_pos pos, t_scene *s, t_matrix m)
{
	t_pixel		pxl;
	t_vector	inter;
	t_vector	normal;
	int			object;

	ray.d.coord[0] = (pos.j - ((s->r[0]) / 2));
	ray.d.coord[1] = (pos.i - ((s->r[1]) / 2));
	normalize(&ray.d);
	ray.d = get_normalized(v_mult_m(ray.d, m));
	object = near_inter(ray, s, &inter, &normal);
	if (object != -1)
	{
		pxl = find_color(s, object, inter, normal);
		pxl.p = (((s->r[1]) - pos.i - 1) * s->size);
		pxl.p += ((s->r[0]) - pos.j - 1) * 4;
		s->data_addr[pxl.p + 2] = pxl.r;
		s->data_addr[pxl.p + 1] = pxl.g;
		s->data_addr[pxl.p + 0] = pxl.b;
	}
}

void	minirt(t_scene *s)
{
	t_pos		pos;
	t_ray		ray;
	t_matrix	m;

	ray.o = s->cameras[s->cam_i].o;
	ray.d.coord[2] = -((s->r[0]) / (2 * (tan(s->cameras[s->cam_i].f / 2))));
	pos.i = 0;
	m = rotation_matrix(s->cameras[s->cam_i].c);
	while (pos.i < s->r[1])
	{
		pos.j = 0;
		while (pos.j < s->r[0])
		{
			create_img(ray, pos, s, m);
			pos.j++;
		}
		pos.i++;
	}
}

void	init_general(t_scene *s)
{
	s->mlx_ptr = mlx_init();
	s->bits_per_pixel = 0;
	s->size = 0;
	s->endian = 0;
	s->lights = 0;
	s->cameras = 0;
	s->objects = 0;
	s->images = 0;
	s->cam_i = 0;
	s->cam_nbr = 0;
	s->r[0] = 0;
	s->r[1] = 0;
}

int		main(int ac, char **av)
{
	t_scene			s;

	init_general(&s);
	if (check_errors(ac, av, &s))
		return (1);
	init_images(&s);
	write(1, "images created\n", 15);
	mlx_hook(s.win_ptr, 2, 1L << 0, ft_event, &s);
	if (!LINUX)
		mlx_hook(s.win_ptr, 17, 1L << 17, ft_cross, &s);
	else
		mlx_hook(s.win_ptr, 33, 1L << 5, ft_cross, &s);
	mlx_loop_hook(s.mlx_ptr, ft_event, &s);
	print_window(s.mlx_ptr, s.win_ptr, s.images[0].img_ptr);
	return (free_scene(0, &s));
}
