#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include "mlx.h"
#include "geometry.h"

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
	sphere.albedo.coord[0] = 64;
	sphere.albedo.coord[1] = 62;
	sphere.albedo.coord[2] = 234;
	sphere.r = 20;
	color = (sphere.albedo.coord[0] * 65536) + (sphere.albedo.coord[1] * 256) + sphere.albedo.coord[2];
	sphere.albedo = get_normalized(sphere.albedo);
	while (i < h)
	{
		if (!i)
		{
			printf("color = %f\n", color);
			printf("r = %uc\n", (((int)color) & 0xFF));
			printf("g = %uc\n", (((int)color >> 8) & 0xFF));
			printf("b = %uc\n", (((int)color >> 16) & 0xFF));
		}
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

void	color_img2(unsigned char *data_addr, int size_line)
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
	sphere.o.coord[0] = -10;
	sphere.o.coord[1] = -5;
	sphere.o.coord[2] = -35;
	sphere.albedo.coord[0] = 140;
	sphere.albedo.coord[1] = 123;
	sphere.albedo.coord[2] = 250;
	sphere.r = 5;
	color = (sphere.albedo.coord[0] * 65536) + (sphere.albedo.coord[1] * 256) + sphere.albedo.coord[2];
	sphere.albedo = get_normalized(sphere.albedo);
	while (i < h)
	{
		if (!i)
		{
			printf("color = %f\n", color);
			printf("r = %uc\n", (((int)color) & 0xFF));
			printf("g = %uc\n", (((int)color >> 8) & 0xFF));
			printf("b = %uc\n", (((int)color >> 16) & 0xFF));
		}
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

void	color_img3(unsigned char *data_addr, int size_line)
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
	sphere.o.coord[0] = 2;
	sphere.o.coord[1] = 2;
	sphere.o.coord[2] = -65;
	sphere.albedo.coord[0] = 240;
	sphere.albedo.coord[1] = 123;
	sphere.albedo.coord[2] = 250;
	sphere.r = 28;
	color = (sphere.albedo.coord[0] * 65536) + (sphere.albedo.coord[1] * 256) + sphere.albedo.coord[2];
	sphere.albedo = get_normalized(sphere.albedo);
	while (i < h)
	{
		if (!i)
		{
			printf("color = %f\n", color);
			printf("r = %uc\n", (((int)color) & 0xFF));
			printf("g = %uc\n", (((int)color >> 8) & 0xFF));
			printf("b = %uc\n", (((int)color >> 16) & 0xFF));
		}
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



int		main(void)
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	unsigned char	*data_addr;
	int				bits_per_pixel;
	int				size_line;
	int				endian;

	bits_per_pixel = 0;
	size_line = 0;
	endian = 0;
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 1024, 1024, "Sphere");
	img_ptr = mlx_new_image(mlx_ptr, 1024, 1024);
	data_addr = (unsigned char *)mlx_get_data_addr(img_ptr, &bits_per_pixel, &size_line, &endian);
	color_img3(data_addr, size_line);
	color_img(data_addr, size_line);
	color_img2(data_addr, size_line);
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
	mlx_loop(mlx_ptr);
	return (0);
}

