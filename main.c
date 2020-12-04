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
	//char			*data_addr;
	int				*bits_per_pixel;
	int				*size_line;
	int				*endian;
	int				ret;
	int				color;

	bits_per_pixel = 0;
	size_line = 0;
	endian = 0;
	if (!(mlx_ptr = mlx_init()))
		return (ft_print_error());
	if (!(win_ptr = mlx_new_window(mlx_ptr, 400, 400, "test1")))
		return (ft_print_error());
	img_ptr = mlx_new_image(mlx_ptr, 300, 300);
	for(int i = 0; i < 401; i++){
		for(int y = 0; y < 401; y++){
			ret = mlx_pixel_put(mlx_ptr, win_ptr, y, i, 0xA116AC);	
		}
	}
	color = mlx_get_color_value(mlx_ptr, 0xFFFFFF);
	bits_per_pixel = &color;
	//data_addr = mlx_get_data_addr(img_ptr, bits_per_pixel, size_line, endian);
	for(int i = 0; i < 301; i++){
		for(int y = 0; y < 301; y++){
			ret = mlx_pixel_put(mlx_ptr, img_ptr, y, i, 0xF0AF3F);
		}
	}
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 50, 50);
	mlx_loop(mlx_ptr);
	//mlx_clear_window(mlx_ptr, win_ptr1);
	//mlx_destroy_window(mlx_ptr, win_ptr1);
	//mlx_clear_window(mlx_ptr, win_ptr2);
	//mlx_destroy_window(mlx_ptr, win_ptr2);
	return (0);
}


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