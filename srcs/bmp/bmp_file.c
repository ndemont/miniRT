/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 11:21:44 by ndemont           #+#    #+#             */
/*   Updated: 2021/02/04 20:21:39 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_fill_bmp(int fd, t_scene *s)
{
	int			i;
	int			int_value;
	short int	short_value;

	write(fd, "BM", 2);
	int_value = 54 + (4 * s->R[0] * s->R[1]);
	write(fd, &int_value, 4);
	write(fd, "\0\0\0\0", 4);
	int_value = 54;
	write(fd, &int_value, 4);
	int_value = 40;
	write(fd, &int_value, 4);
	int_value = s->R[0];
	write(fd, &int_value, 4);
	int_value = s->R[1];
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

	i = s->R[0] - 1;
	while (i >= 0)
	{
		j = 0;
		while (j < s->R[1])
		{
			pixel = (i * s->size_line) + (j * 4);
			write(fd, &s->data_addr[pixel + 0], 3);
			write(fd, "\0", 1);
			j++;
		}
		i--;
	}
}

int		bmp_yay(t_scene *s)
{
	int				fd;

	fd = open("new.bmp", O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (fd < 0)
		return (printf("Error: can not open file.\n"));
	ft_fill_bmp(fd, s);
	ft_fill_pixel(fd, s);
	close(fd);
	return (0);
}
