/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 11:21:44 by ndemont           #+#    #+#             */
/*   Updated: 2021/02/12 13:18:30 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_fill_bmp(int fd, t_scene *s)
{
	int			i;
	int			int_value;
	short int	short_value;

	write(fd, "BM", 2);
	int_value = 54 + (4 * (int)s->r[0] * (int)s->r[1]);
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

	i = (int)s->r[0] - 1;
	while (i >= 0)
	{
		j = 0;
		while (j < (int)s->r[1])
		{
			pixel = (i * s->size) + (j * 4);
			write(fd, &s->data_addr[pixel], 3);
			write(fd, "\0", 1);
			j++;
		}
		i--;
	}
}

void	bmp_image(t_scene *s)
{
	s->cam_i = 0;
	set_plan(s);
	s->r[0] = s->reso.width;
	s->r[1] = s->reso.height;
	if (s->reso.width > MAX_WIDTH_BMP || s->reso.width < 0)
	{
		ft_printf("Oooops :/ your width resolution is too high for my bmp:\n\
given resolution:\t%d\n\
hardcoded to HD:\t%d\n\n", s->reso.width, MAX_WIDTH_BMP);
		s->r[0] = MAX_WIDTH_BMP;
	}
	if (s->reso.height > MAX_HEIGHT_BMP || s->reso.height < 0)
	{
		ft_printf("Oooops :/ your height resolution is too high for my bmp:\n\
given resolution:\t%d\n\
hardcoded to HD:\t%d\n\n", s->reso.height, MAX_HEIGHT_BMP);
		s->r[1] = MAX_HEIGHT_BMP;
	}
	ft_new_img(s);
}

char	*save_bmp(t_scene *s)
{
	int				fd;

	bmp_image(s);
	fd = open("new.bmp", O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (fd < 0)
		return ("Error 3: Cannot open file.");
	ft_fill_bmp(fd, s);
	ft_fill_pixel(fd, s);
	close(fd);
	return (0);
}
