#include "minirt.h"

void	color_img(unsigned char *data_addr, int size_line)
{
	int			i;
	int			j;
	t_ray		ray;
	t_light		light;
	t_sphere	sphere;
	t_vector	inters;
	t_vector	normal;
	t_vector	new;
	int			pixel;
	float		fov;
	t_vector	intensity;
	int			ret;
	int			w;
	int			h;
	float		color;

	(void)size_line;
	w = 1024;
	h = 1024;
	i = 0;
	fov = 60 * (M_PI / 180);
	light.o.coord[0] = 10;
	light.o.coord[1] = 50;
	light.o.coord[2] = -20;
	light.i = 1000000;
	ray.o.coord[0] = 0;
	ray.o.coord[1] = 0;
	ray.o.coord[2] = 0;
	sphere.o.coord[0] = 0;
	sphere.o.coord[1] = 0;
	sphere.o.coord[2] = -55;
	sphere.albedo.coord[0] = 17;
	sphere.albedo.coord[1] = 137;
	sphere.albedo.coord[2] = 100;
	sphere.r = 20;
	color = (sphere.albedo.coord[0] * 65536) + (sphere.albedo.coord[1] * 256) + sphere.albedo.coord[2];
	sphere.albedo = get_normalized(sphere.albedo);
	while (i < h)
	{
		j = 0;
		while (j < w)
		{
			ray.d.coord[0] = j - (w/2);
			ray.d.coord[1] = i - (h/2);
			ray.d.coord[2] = -w / (2*(tan(fov / 2)));
			normalize(&ray.d);
			ret = inter(ray, sphere, &inters, &normal);
			if (ret)
			{
				new = v_minus_v(light.o, inters); 
				new = get_normalized(new);
				intensity.coord[0] = 0.001 * light.i * scalaire(new, normal) / (get_norme_2(v_minus_v(light.o, inters)));
				intensity.coord[1] = 0.001 * light.i * scalaire(new, normal) / (get_norme_2(v_minus_v(light.o, inters)));
				intensity.coord[2] = 0.001 * light.i * scalaire(new, normal) / (get_norme_2(v_minus_v(light.o, inters)));
				if (intensity.coord[0] < 0)
					intensity.coord[0] = 0;
				if (intensity.coord[1] < 0)
					intensity.coord[1] = 0;
				if (intensity.coord[2] < 0)
					intensity.coord[2] = 0;
				if (intensity.coord[0] > 255)
					intensity.coord[0] = 255;
				if (intensity.coord[1] > 255)
					intensity.coord[1] = 255;
				if (intensity.coord[2] > 255)
					intensity.coord[2] = 255;
				pixel = ((h -i -1) * size_line) + (j * 4);
				data_addr[pixel + 0] = (((int)color) & 0xFF) * intensity.coord[0];
				data_addr[pixel + 1] = (((int)color >> 8) & 0xFF) * intensity.coord[1];
				data_addr[pixel + 2] = (((int)color >> 16) & 0xFF) * intensity.coord[2];
			}
			j++;
		}
		i++;
	}
}

void	color_img2(unsigned char *data_addr, int size_line, t_sphere sphere, t_light light, t_ray ray)
{
	int			i;
	int			j;
	t_vector	inters;
	t_vector	normal;
	t_vector	new;
	int			pixel;
	float		fov;
	float		intensity;
	int			ret;
	int			w;
	int			h;

	(void)size_line;
	w = 1024;
	h = 1024;
	i = 0;
	fov = 60 * (M_PI / 180);
	while (i < h)
	{
		j = 0;
		while (j < w)
		{
			ray.d.coord[0] = j - (w/2);
			ray.d.coord[1] = i - (h/2);
			ray.d.coord[2] = -w / (2*(tan(fov / 2)));
			normalize(&ray.d);
			ret = inter(ray, sphere, &inters, &normal);
			if (ret)
			{
				new = v_minus_v(light.o, inters); 
				new = get_normalized(new);
				intensity = light.i * scalaire(new, normal) / (get_norme_2(v_minus_v(light.o, inters)));
				if (intensity < 0)
					intensity = 0;
				if (intensity > 255)
					intensity = 255;
				pixel = ((h -i -1) * size_line) + (j * 4);
				data_addr[pixel + 0] = sphere.albedo.coord[0] * intensity;
				data_addr[pixel + 1] = sphere.albedo.coord[1] * intensity;
				data_addr[pixel + 2] = sphere.albedo.coord[2] * intensity;
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

//void 	create_window

int		main(int ac, char **av)
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	unsigned char	*data_addr;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	int				ret;
	t_ray			ray;
	t_light			light;
	t_sphere		sphere;

	light.o.coord[0] = 10;
	light.o.coord[1] = 50;
	light.o.coord[2] = -20;
	light.i = 200000;
	ray.o.coord[0] = 0;
	ray.o.coord[1] = 0;
	ray.o.coord[2] = 0;
	sphere.o.coord[0] = -10;
	sphere.o.coord[1] = -5;
	sphere.o.coord[2] = -35;
	sphere.albedo.coord[0] = 45;
	sphere.albedo.coord[1] = 190;
	sphere.albedo.coord[2] = 100;
	sphere.r = 5;
	sphere.albedo = get_normalized(sphere.albedo);
	if (ac < 2 || ac > 3)
		return (print_errors(1));
	if (!check_file(av[1]))
		return (print_errors(2));
	if (ac == 3)
		if (ft_strcmp(av[2], "-save"))
			return (print_errors(5));
	if ((ret = check_parsing(av[1])))
		return (print_errors(ret));
	bits_per_pixel = 0;
	size_line = 0;
	endian = 0;
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 1024, 1024, "Sphere");
	img_ptr = mlx_new_image(mlx_ptr, 1024, 1024);
	data_addr = (unsigned char *)mlx_get_data_addr(img_ptr, &bits_per_pixel, &size_line, &endian);
	color_img(data_addr, size_line);
	color_img2(data_addr, size_line, sphere, light, ray);
	print_window(mlx_ptr, win_ptr, img_ptr);
	return (0);
}

