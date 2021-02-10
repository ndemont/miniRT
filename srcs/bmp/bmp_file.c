/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 11:21:44 by ndemont           #+#    #+#             */
/*   Updated: 2021/02/10 17:18:05 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_fill_bmp(int fd, t_scene *s)
{
	int			i;
	int			int_value;
	short int	short_value;

	write(fd, "BM", 2);
	int_value = 54 + (4 * s->r[0] * s->r[1]);
	write(fd, &int_value, 4);
	write(fd, "\0\0\0\0", 4);
	int_value = 54;
	write(fd, &int_value, 4);
	int_value = 40;
	write(fd, &int_value, 4);
	int_value = s->r[0];
	write(fd, &int_value, 4);
	int_value = s->r[1];
	write(fd, &int_value, 4);
	short_value = 1;
	write(fd, &short_value, 2);
	short_value = 32;
	write(fd, &short_value, 2);
	i = 0;
	while (i++ < 24)
		write(fd, "\0", 1);
}

void	ft_fill_pixel(int fd, t_scene *s)
{
	int		i;
	int		j;
	int		pixel;

	i = s->r[0] - 1;
	while (i >= 0)
	{
		j = 0;
		while (j < s->r[1])
		{
			pixel = (i * s->size) + (j * 4);
			write(fd, &s->data_addr[pixel + 0], 3);
			write(fd, "\0", 1);
			j++;
		}
		i--;
	}
}

void	bmp_image(t_scene *s)
{
	t_img	*images;

	s->cam_i = 0;
	images = malloc(sizeof(t_img));
	set_plan(s);
	images[0] = ft_new_img(s);
}

int		save_bmp(t_scene *s)
{
	int				fd;

	bmp_image(s);
	fd = open("new.bmp", O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (fd < 0)
		return (printf("Error: can not open file.\n"));
	ft_fill_bmp(fd, s);
	ft_fill_pixel(fd, s);
	close(fd);
	free_scene(0, s);
	exit(0);
	return (0);
}
