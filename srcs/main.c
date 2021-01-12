#include "minirt.h"

void	color_img(t_scene *s)
{
	int			i;
	int			j;
	t_ray		ray;
	t_vector	inters;
	t_vector	normal;
	t_vector	new;
	int			pixel;
	float		intensity;
	int			ret;
	t_object	*ret2;
	int			w;
	int			h;
	float		color;

	w = s->R[0];
	h = s->R[1];
	i = 0;
	(void)ret;
	ray.o.coord[0] = 0;
	ray.o.coord[1] = 0;
	ray.o.coord[2] = 0;
	while (i < s->R[1])
	{
		j = 0;
		while (j < s->R[0])
		{
			ray.d.coord[0] = j - ((s->R[0])/2);
			ray.d.coord[1] = i - ((s->R[1])/2);
			ray.d.coord[2] = -(s->R[0]) / (2*(tan(s->cameras[0].f / 2)));
			normalize(&ray.d);
			ret2 = inter2(ray, s->objects, &inters, &normal);
			if (ret2)
			{
				color = (ret2->c.coord[0] * 65536) + (ret2->c.coord[1] * 256) + ret2->c.coord[2];
				new = v_minus_v(s->lights[0].o, inters); 
				new = get_normalized(new);
				intensity = (s->lights[0].i * 2000) * scalaire(new, normal) / (get_norme_2(v_minus_v(s->lights[0].o, inters)));
				if (intensity < 0)
					intensity = 0;
				if (intensity > 1)
					intensity = 1;
				pixel = ((h -i -1) * s->size_line) + (j * 4);
				s->data_addr[pixel + 0] = (((int)color) & 0xFF) * intensity;
				s->data_addr[pixel + 1] = (((int)color >> 8) & 0xFF) * intensity;
				s->data_addr[pixel + 2] = (((int)color >> 16) & 0xFF) * intensity;
			}
			j++;
		}
		i++;
	}
}

int		print_errors(int error)
{
	if (error == 1)
		ft_printf("Wrong number of arguments.\n");
	if (error == 2)
		ft_printf("Wrong type of file\n");
	if (error == 3)
		ft_printf("Wrong configuration of the file\n");
	if (error == 5)
		ft_printf("Wrong option\n");
	return (1);
}

void	print_window(void *mlx_ptr, void *win_ptr, void *img_ptr)
{
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
	mlx_loop(mlx_ptr);
}

void	init_general(t_scene *s)
{
	s->mlx_ptr = mlx_init();
	s->bits_per_pixel = 0;
	s->size_line = 0;
	s->endian = 0;
	s->win_ptr = mlx_new_window(s->mlx_ptr, s->R[0], s->R[1], "Sphere");
	s->img_ptr = mlx_new_image(s->mlx_ptr, s->R[0], s->R[1]);
	s->data_addr = (unsigned char *)mlx_get_data_addr(s->img_ptr, &(s->bits_per_pixel), &(s->size_line), &(s->endian));
}

int		main(int ac, char **av)
{
	int				ret;
	t_scene			s;

	if (ac < 2 || ac > 3)
		return (print_errors(1));
	if (!check_file(av[1]))
		return (print_errors(2));
	if (ac == 3)
		if (ft_strcmp(av[2], "-save"))
			return (print_errors(5));
	if ((ret = check_parsing(av[1], &s)))
		return (print_errors(ret));
	init_general(&s);
	color_img(&s);
	print_window(s.mlx_ptr, s.win_ptr, s.img_ptr);
	return (0);
}