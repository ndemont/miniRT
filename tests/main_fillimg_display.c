#include "mlx.h"
#include <unistd.h>
#include <stdio.h>

int	ft_print_error(void)
{
	write(1, "Error\n", 6);
	return (1);
}

int		main(void)
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	char			*data_addr;
	int				*data_addr2;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	int				color;
	int				pixel;
	int				x;
	int				y;

	bits_per_pixel = 0;
	size_line = 0;
	endian = 0;
	pixel = 0;
	color = 0xA1D69E;
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 400, 400, "test1");
	img_ptr = mlx_new_image(mlx_ptr, 400, 400);
	data_addr = mlx_get_data_addr(img_ptr, &bits_per_pixel, &size_line, &endian);
	data_addr2 = (int *)mlx_get_data_addr(img_ptr, &bits_per_pixel, &size_line, &endian);
	printf("pixel bits = %d\n", bits_per_pixel);
	printf("line bytes = %d\n", bits_per_pixel);
	if (bits_per_pixel != 32)
    	color = mlx_get_color_value(mlx_ptr, color);
	y = 0;
	while (y <= 400)
	{
		x = 0;
		while (x <= 400)
		{
			data_addr2[(y * (size_line / 4)) + x] = color;
			//pixel = (y * size_line) + (x * 4);
			//if (endian == 1)
			//{
			//	data_addr[pixel + 0] = (color >> 24);
			//	data_addr[pixel + 1] = (color >> 16) & 0xFF;
			//	data_addr[pixel + 2] = (color >> 8) & 0xFF;
			//	data_addr[pixel + 3] = (color) & 0xFF;
			//}
			//else if (endian == 0)
			//{
			//	data_addr[pixel + 0] = (color) & 0xFF;
			//	data_addr[pixel + 1] = (color >> 8) & 0xFF;
			//	data_addr[pixel + 2] = (color >> 16) & 0xFF;
			//	data_addr[pixel + 3] = (color >> 24);
			//}
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
	mlx_loop(mlx_ptr);
	return (0);
}

	//for(int i = 0; i < 401; i++){
	//	for(int y = 0; y < 401; y++){
	//		ret = mlx_pixel_put(mlx_ptr, win_ptr, y, i, 0xA116AC);	
	//	}
	//}
	//mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 50, 50);
	//mlx_pixel_put(mlx_ptr, win_ptr, 200, 200, 0xFFFFFF);
	//color = mlx_get_color_value(mlx_ptr, 0xFFFFFF);
	//bits_per_pixel = &color;
	//ret = 300;
	//size_line = &ret;
	//data_addr = mlx_get_data_addr(img_ptr, bits_per_pixel, size_line, endian);
	//for(int i = 0; i < 301; i++){
	//	for(int y = 0; y < 301; y++){
	//		ret = mlx_pixel_put(mlx_ptr, img_ptr, y, i, 0xF0AF3F);
	//	}

//mlx_clear_window(mlx_ptr, win_ptr1);
	//mlx_destroy_window(mlx_ptr, win_ptr1);
	//mlx_clear_window(mlx_ptr, win_ptr2);
	//mlx_destroy_window(mlx_ptr, win_ptr2);

//if (!ft_strcmp(av[2]], "-save")
	//{
	//	une fonction qui fait un screen shot et le sauvergarde
	//	.bmp
	//}

//int		parsing()
//{
//	strlen(av[1])
//	puis check de
//	av[1][strlen -1] = t;
//	av[1][strlen - 2] = r;
//	av[1][strlen - 3] = r;

//	size > 0;
//	one argument per line
//	chaque majuscule nest declaree quune fois
//}