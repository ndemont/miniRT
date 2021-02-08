#include "minirt.h"

int		check_file(char *filename)
{
	int len;

	len = ft_strlen(filename);
	if (ft_strcmp(".rt", &filename[len - 3]))
		return (0);
	return (1);
}

t_matrix	rotation_matrix(t_scene s)
{
	t_matrix matrix;
	t_vector forward;
	t_vector right;
	t_vector up;

	forward = get_normalized(v_mult_i(s.cameras[s.cam_i].c, -1));
	if (abs((int)forward.coord[1]) == 1)
		right = get_normalized(init_vector(1, 0, 0));
	else
		right = get_normalized(init_vector(0, 1, 0));
	right = v_produit_v(right, forward);
	up = v_produit_v(forward, right);
	matrix.r1 = right;
	matrix.r2 = up;
	matrix.r3 = forward;
	return (matrix);
}

void	color_img(t_scene *s)
{
	int			i;
	int			j;
	t_ray		ray;
	t_vector	inters;
	t_vector	normal;
	t_vector	new;
	t_vector	lights;
	int			pixel;
	float		intensity;
	int			ret;
	t_matrix	m;

	ray.o = s->cameras[s->cam_i].o;
	printf("ray origin %d:\nx = %f\ny = %f\nz = %f\n", s->cam_i, ray.o.coord[0], ray.o.coord[1], ray.o.coord[2]);
 	i = 0;
	set_plan(s);
	m = rotation_matrix(*s);
	while (i < s->R[1])
	{
		j = 0;
		while (j < s->R[0])
		{
			ray.d.coord[0] = (j - ((s->R[0])/2));
			ray.d.coord[1] = (i - ((s->R[1])/2));
			ray.d.coord[2] = -((s->R[0]) / (2*(tan(s->cameras[s->cam_i].f / 2))));
			normalize(&ray.d);
			ray.d = get_normalized(v_mult_m(ray.d, m));
			ret = closest_inter(ray, s, &inters, &normal);
			if (ret != -1)
			{	
				intensity = 0;
				new = v_minus_v(s->lights[0].o, inters);
				new = get_normalized(new);
				lights = find_intensity(inters, &intensity, normal, *s);
				pixel = (((s->R[1]) -i -1) * s->size_line) + ((s->R[0]) -j -1) * 4;
				s->data_addr[pixel + 2] = fmin(s->objects[ret].c.coord[0] , lights.coord[0]) * intensity;
				s->data_addr[pixel + 1] = fmin(s->objects[ret].c.coord[1] , lights.coord[1]) * intensity;
				s->data_addr[pixel + 0] = fmin(s->objects[ret].c.coord[2] , lights.coord[2]) * intensity;
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

int		print_errors2(char *error)
{
	ft_printf("%s\n", error);
	return (1);
}

void	print_window(void *mlx_ptr, void *win_ptr, void *img_ptr)
{
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
	mlx_loop(mlx_ptr);
}

t_img	ft_new_img(t_scene *s, int i)
{
	t_img img;

	img.img_ptr = mlx_new_image(s->mlx_ptr, s->R[0], s->R[1]);
	s->data_addr = (unsigned char *)mlx_get_data_addr(img.img_ptr, &(s->bits_per_pixel), &(s->size_line), &(s->endian));
	printf("data created for %d\n", i);
	color_img(s);
	return (img);
}

t_img	*ft_load_imgs(t_scene *s)
{
	int 	i;
	t_img	*images;

	i = 0;
	images = malloc(sizeof(t_img) * s->cam_nbr);
	while (i < s->cam_nbr)
	{
		printf("i = %d\n", 1);
		printf("cam nbr = %d\n", s->cam_nbr);
		s->cam_i = i;
		images[i] = ft_new_img(s, i);
		printf("%d done\n", i);
		i++;
	}
	return (images);
}

void	init_general(t_scene *s)
{
	printf("initialization");
	s->mlx_ptr = mlx_init();
	s->bits_per_pixel = 0;
	s->size_line = 0;
	s->endian = 0;
	//mlx_get_screen_size(s->mlx_ptr, &x, &y);
	//printf("x = %d - y = %d\n", x, y);
	s->win_ptr = mlx_new_window(s->mlx_ptr, s->R[0], s->R[1], "miniRT");
	s->images = ft_load_imgs(s);
	s->cam_i = 0;
}

int		main(int ac, char **av)
{
	char 			*error;
	t_scene			s;

	if (ac < 2 || ac > 3)
		return (print_errors(1));
	if (!check_file(av[1]))
		return (print_errors(2));
	if (ac == 3)
		if (ft_strcmp(av[2], "-save"))
			return (print_errors(5));
	if ((error = check_parsing(av[1], &s)))
		return (print_errors2(error));
	init_general(&s);
	if (!mlx_hook(s.win_ptr, 2, 1L<<0, ft_event, &s))
		return (0);
	if (!mlx_hook(s.win_ptr, 17, 1L<<17, ft_cross, &s))
		return (0);
	//if (!mlx_hook(s.win_ptr, 33, 1L<<5, ft_cross, &s))
	//	return (0);
	mlx_loop_hook(s.mlx_ptr, ft_event, &s);
	//if (!mlx_hook(s.win_ptr, 25, 1L<<18, ft_event, &s))
	//	return (0);
	//mlx_loop_hook(s.mlx_ptr, ft_cross, &s);
	bmp_yay(&s);
	print_window(s.mlx_ptr, s.win_ptr, s.images[0].img_ptr);
	return (0);
}

