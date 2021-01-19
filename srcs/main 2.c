#include "minirt.h"

int		check_shadow(t_scene *s, t_vector inter, t_vector N)
{
	t_ray		ray;
	double 		ret;
	float		d;
	int			i;
	float		t;

	i = 0;
	t = 1E99;
	inter = v_plus_v(inter, v_mult_i(N, 0.01));
	ray.o = inter;
	ray.d = v_minus_v(s->lights[0].o, inter);
	normalize(&ray.d);
	d = get_norme_2(v_minus_v(s->lights[0].o, inter));
	while (s->objects[i].type != -1)
	{
		ret = inter_type(ray, s->objects[i], &inter, &N);
		if (ret < t)
			t = ret;
		i++;
	}
	if (t < 1E99)
	{
		t *= t;
		if (t < d)
			t = 1;
		else
			t = 0;
	}
	else 
		t = 0;
	return (t);
}

void	color_img(t_scene *s)
{
	int			i;
	int			j;
	t_ray		ray;
	t_vector	inters;
	t_vector	normal;
	//t_vector 	N1;
	//t_vector 	N2;
	t_vector	new;
	int			pixel;
	float		intensity;
	int			ret;
	int			ret2;
	//float		scal1;
	//float		scal2;
	//float		angle;
	float		color;

	ray.o = s->cameras[0].o;
	i = 0;
	intensity = 1;
	printf("cam = %f/%f/%f\n", s->cameras[0].c.coord[0], s->cameras[0].c.coord[1], s->cameras[0].c.coord[2]);
	while (i < s->R[1])
	{
		j = 0;
		while (j < s->R[0])

		{
			ray.d.coord[0] = (j - ((s->R[0])/2));
			ray.d.coord[1] = (i - ((s->R[1])/2));
			ray.d.coord[2] = -((s->R[0]) / (2*(tan(s->cameras[0].f / 2))));
			normalize(&ray.d);	
			//ray.d.coord[0] += 0.1 * s->cameras[0].c.coord[0];
			ret = closest_inter(ray, *s, &inters, &normal);
			if (ret != -1)
			{		
				color = (s->objects[ret].c.coord[0] * 65536) + (s->objects[ret].c.coord[1] * 256) + s->objects[ret].c.coord[2];
				new = v_minus_v(s->lights[0].o, inters);
				new = get_normalized(new);
				intensity = (s->lights[0].i * 2000 * scalaire(new, normal));
				intensity = intensity / (get_norme_2(v_minus_v(s->lights[0].o, inters)));
				ret2 = check_shadow(s, inters, normal);
				if (intensity < 0)
					intensity = 0;
				else if (intensity > 1)
					intensity = 1;
				if (ret2 == 1)
					intensity *= 0.1;
				intensity += s->A.i;
				if (intensity > 1)
					intensity = 1;
				pixel = (((s->R[1]) -i -1) * s->size_line) + ((s->R[0]) -j -1) * 4;
				s->data_addr[pixel] = (((int)color) & 0xFF) * intensity;
				s->data_addr[pixel + 1] = ((((int)color) >> 8) & 0xFF) * intensity;
				s->data_addr[pixel + 2] = ((((int)color) >> 16) & 0xFF) * intensity;
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
	write(1, "test 00\n", 9);
	color_img(&s);
	print_window(s.mlx_ptr, s.win_ptr, s.img_ptr);
	return (0);
}