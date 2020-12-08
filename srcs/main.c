#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include "mlx.h"
#include "geometry.h"

void	color_img(int color, int *data_addr, int size_line)
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
	float		intensity;
	int			ret;
	int			w;
	int			h;

	(void)color;
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
	sphere.albedo.coord[0] = 1;
	sphere.albedo.coord[1] = 0;
	sphere.albedo.coord[2] = 0;
	sphere.r = 20;
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
				intensity = scalaire(new, normal);
				if (intensity < 0)
					intensity = 0;
				intensity = intensity / (get_norme_2(v_minus_v(light.o, inters)));
				intensity = intensity * light.i;
				if (intensity < 0)
					intensity = 0;
				if (intensity > 255)
					intensity = 255;
				//pixel = (i * size_line) + (j * 4);
				data_addr[((h -i -1) * (size_line / 4)) + j] = intensity;
				//data_addr[(((h -i -1) * w) + j) * (3 + 0)] = intensity;
				//data_addr[(((h -i -1) * w) + j) * (3 + 1)] = intensity;
				//data_addr[(((h -i -1) * w) + j) * (3 + 2)] = intensity;
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
	int				*data_addr;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	int				color;

	bits_per_pixel = 0;
	size_line = 0;
	endian = 0;
	color = 0x3E987A;
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 1024, 1024, "Sphere");
	img_ptr = mlx_new_image(mlx_ptr, 1024, 1024);
	data_addr = (int *)mlx_get_data_addr(img_ptr, &bits_per_pixel, &size_line, &endian);
	color_img(color, data_addr, size_line);
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
	mlx_loop(mlx_ptr);
	return (0);
}

