#include "mlx.h"
#include <unistd.h>
#include <stdio.h>
#include <math.h>


int		ft_power(int nb, int power)
{
	int rslt;

	rslt = 1;
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	while (power > 0)
	{
		rslt = nb * rslt;
		power--;
	}
	return (rslt);
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
	int				pixel;
	int				ca;
	int				cb;
	int				d;
	int				x;
	int				y;
	//int 			rslt;
	//t_sp			sphere;
	//t_R				resolution;
	//t_c				camera;

	//resolution.x = 1000;
	//resolution.y = 700;

	//camera.pov[0] = 0;
	//camera.pov[0] = 0;
	//camera.pov[0] = 0;

	//sphere.p[0] = -50;
	//sphere.p[1] = 0;
	//sphere.p[2] = 20;
	//sphere.r = 20 / 2;
	//sphere.rgb[0] = 255;
	//sphere.rgb[1] = 0;
	//sphere.rgb[2] = 0;

	bits_per_pixel = 0;
	size_line = 0;
	endian = 0;
	pixel = 0;
	ca = 450;
	cb = 450;
	d = 700;
	color = 0xFF0000;
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 1000, 1000, "Sphere");
	img_ptr = mlx_new_image(mlx_ptr, 1000, 1000);
	data_addr = (int *)mlx_get_data_addr(img_ptr, &bits_per_pixel, &size_line, &endian);
	y = 0;
	while (y < 1000)
	{ 
		x = 0;
		while (x < 1000)
		{
			//rslt = ft_power(x - ca, 2) + ft_power(y - cb, 2);
			//if (rslt <= ft_power(d / 2, 2))
			data_addr[(y * (size_line / 4)) + x] = color;
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
	mlx_loop(mlx_ptr);
	return (0);
}