#include "mlx.h"
#include <unistd.h>
#include <stdio.h>
#include <math.h>

int		ft_iterative_power(int nb, int power)
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
	int 			rslt;

	bits_per_pixel = 0;
	size_line = 0;
	endian = 0;
	pixel = 0;
	ca = 100;
	cb = 100;
	d = 100;
	color = 0xA1D69E;
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 400, 400, "Circle");
	img_ptr = mlx_new_image(mlx_ptr, 200, 200);
	data_addr = (int *)mlx_get_data_addr(img_ptr, &bits_per_pixel, &size_line, &endian);
	y = 0;
	while (y <= 400)
	{
		x = 0;
		while (x <= 400)
		{
			rslt = ft_iterative_power(x - ca, 2) + ft_iterative_power(y - cb, 2);
			if (rslt <= ft_iterative_power(d / 2, 2))
				data_addr[(y * (size_line / 4)) + x] = color;
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 100, 100);
	mlx_loop(mlx_ptr);
	return (0);
}