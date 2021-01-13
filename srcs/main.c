#include "minirt.h"

float	set_color(float r, float g, float b, float i)
{
	float color;

	r = r * i;
	if (r < 1)
		r = 0;
	if (r > 255)
		r = 255;
	g = g * i;
	if (g < 1)
		g = 0;
	if (g > 255)
		g = 255;
	b = b * i;
	if (b < 1)
		b = 0;
	if (b > 255)
		b = 255;
	color = (r * 65536) + (g * 256) + b;
	return (color);
}

int		check_shadow(t_scene *s, t_vector inter)
{
	t_ray		ray;
	double 		ret;
	double		d;
	t_vector	normal;
	t_vector	shadow;

	normal = get_normalized(v_minus_v(inter, s->lights[0].o));
	ray.o.coord[0] = inter.coord[0] + 0.01; //* normal.coord[0];
	ray.o.coord[1] = inter.coord[1] + 0.01; //* normal.coord[1];
	ray.o.coord[2] = inter.coord[2] + 0.01; //* normal.coord[2];
	ray.d.coord[0] = s->lights[0].o.coord[0] - inter.coord[0];
	ray.d.coord[1] = s->lights[0].o.coord[1] - inter.coord[1];
	ray.d.coord[2] = s->lights[0].o.coord[2] - inter.coord[2];
	normalize(&ray.d);
	ret = inter3(ray, s->objects, &shadow, &normal);
	//printf(" ret = %f\n\n", ret);
	if (ret < 1E99)
	{
		ret *= ret;
		d = get_norme_2(v_minus_v(s->lights[0].o, inter));
		//printf(" distance 2= %f\n", d);
		//printf(" ret = %f\n\n", ret);
		if (ret < d)
			ret = 1;
		else
			ret = 0;
	}
	else 
		ret = 0;
	return (ret);
}

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
	int			ret2;
	float		color;

	ray.o.coord[0] = 0;
	ray.o.coord[1] = 0;
	ray.o.coord[2] = 0;
	(void)ret2;
	i = 0;
	intensity = 1;
	while (i < s->R[1])
	{
		j = 0;
		while (j < s->R[0])
		{
			ray.d.coord[0] = j - ((s->R[0])/2);
			ray.d.coord[1] = i - ((s->R[1])/2);
			ray.d.coord[2] = -(s->R[0]) / (2*(tan(s->cameras[0].f / 2)));
			normalize(&ray.d);
			ret = inter2(ray, s->objects, &inters, &normal);
			if (ret != -1)
			{		
				color = (s->objects[ret].c.coord[0] * 65536) + (s->objects[ret].c.coord[1] * 256) + s->objects[ret].c.coord[2];
				new = v_minus_v(s->lights[0].o, inters); 
				new = get_normalized(new);
				intensity = (s->lights[0].i * 2000 * scalaire(new, normal)) / (get_norme_2(v_minus_v(s->lights[0].o, inters)));
				ret2 = check_shadow(s, inters);
				if (intensity < 0)
					intensity = 0;
				if (intensity > 1)
					intensity = 1;
				else if (ret2 == 1)
					intensity *= 0.5;
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
	color_img(&s);
	print_window(s.mlx_ptr, s.win_ptr, s.img_ptr);
	return (0);
}