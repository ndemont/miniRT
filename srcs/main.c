#include "minirt.h"

float		check_shadow(t_scene *s, t_vector inter, t_vector N, int l)
{
	t_ray		ray;
	double 		ret;
	float		d;
	int			i;
	float 		t;

	inter = v_plus_v(inter, v_mult_i(N, 0.01));
	ray.o = inter;
	t = 1E99;
	ray.d = v_minus_v(s->lights[l].o, inter);
	normalize(&ray.d);
	d = get_norme_2(v_minus_v(s->lights[l].o, inter));
	i = 0;
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
			t = 0.3;
		else
			t = 1;
	}
	else 
		t = 1;
	return (t);
}

t_vector	find_intensity(t_vector inter, float *fint, t_vector N, t_scene s)
{
	int			i;
	float		intensity;
	t_vector	color;
	int			count;	
	t_vector	new;


	i = 0;
	count = 0;
	color.coord[0] = 0;
	color.coord[1] = 0;
	color.coord[2] = 0;
	while (s.lights[i].i != -1)
	{
		new = get_normalized(v_minus_v(s.lights[i].o, inter));
		intensity = (s.lights[i].i * 1000 * scalaire(new, N));
		intensity = intensity / (get_norme_2(v_minus_v(s.lights[i].o, inter)));
		if (intensity < 0)
		{
			intensity = 0;
			count++;
		}
		if (intensity > 1)
			intensity = 1;
		intensity = intensity * (check_shadow(&s, inter, N, i));
		*fint = *fint + intensity;
		//printf("intensity = %f\n", intensity);
		color = v_plus_v(v_mult_i(s.lights[i].c, intensity), color);
		//printf("color = %f/%f/%f\n", color.coord[0], color.coord[1], color.coord[2]);
		i++;
	}
	//color = v_plus_v(v_mult_i(s.A.color, s.A.i), color);
	if (*fint < 0)
		*fint = 0;
	if (*fint > 1)
		*fint = 1;
	color = v_div_i(color, i);
	//printf("color = %f/%f/%f\n", color.coord[0], color.coord[1], color.coord[2]);

	return (color);
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


	ray.o = s->cameras[0].o;
 	i = 0;
	while (i < s->R[1])
	{
		j = 0;
		while (j < s->R[0])
		{
			ray.d.coord[0] = (j - ((s->R[0])/2));
			ray.d.coord[1] = (i - ((s->R[1])/2));
			ray.d.coord[2] = -((s->R[0]) / (2*(tan(s->cameras[0].f / 2))));
			normalize(&ray.d);	
			ret = closest_inter(ray, *s, &inters, &normal);
			if (ret != -1)
			{	
				intensity = 0;
				new = v_minus_v(s->lights[0].o, inters);
				new = get_normalized(new);
				lights = find_intensity(inters, &intensity, normal, *s);
				//intensity = (s->lights[0].i * 2000 * scalaire(new, normal));
				//intensity = intensity / (get_norme_2(v_minus_v(s->lights[0].o, inters)));
				//intensity = find_intensity(inters, s->lights, normal);
				//ret2 = check_shadow(s, inters, normal);
				///if (intensity < 0)
				///	intensity = 0;
				//intensity *= ret2;
				intensity += s->A.i;
				if (intensity > 1)
					intensity = 1;
				pixel = (((s->R[1]) -i -1) * s->size_line) + ((s->R[0]) -j -1) * 4;
				// s->data_addr[pixel + 2] = (s->objects[ret].c.coord[0] + lights.coord[0]) / 2;
				// s->data_addr[pixel + 1] = (s->objects[ret].c.coord[1] + lights.coord[1]) / 2;
				// s->data_addr[pixel + 0] = (s->objects[ret].c.coord[2] + lights.coord[2]) / 2;
				s->data_addr[pixel + 2] = ((s->objects[ret].c.coord[0] + lights.coord[0]) / 2) * intensity;
				s->data_addr[pixel + 1] = ((s->objects[ret].c.coord[1] + lights.coord[1]) / 2) * intensity;
				s->data_addr[pixel + 0] = ((s->objects[ret].c.coord[2]+ lights.coord[2]) / 2) * intensity;
				// s->data_addr[pixel + 2] = fmin(s->objects[ret].c.coord[0], s->lights[0].c.coord[0]) * intensity;
				// s->data_addr[pixel + 1] = fmin(s->objects[ret].c.coord[1], s->lights[0].c.coord[1]) * intensity;
				// s->data_addr[pixel + 0] = fmin(s->objects[ret].c.coord[2], s->lights[0].c.coord[2]) * intensity;
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