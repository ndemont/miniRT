/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_conversion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 11:16:55 by ndemont           #+#    #+#             */
/*   Updated: 2020/11/29 20:57:34 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "libft.h"

void	ft_putchar_n_fd(char c, int n)
{
	while (n > 0)
	{
		ft_putchar_fd(c, 1);
		n--;
	}
}

void	ft_puthex_min_fd(long n, int fd)
{
	static char	base[16] = "0123456789abcdef";
	int			c;
	long		nb;

	if (n < 0)
	{
		write(fd, "-", 1);
		nb = -(long)n;
	}
	else
		nb = n;
	if ((nb / 16) > 0)
		ft_puthex_min_fd((nb / 16), fd);
	c = (nb % 16);
	write(fd, &base[c], 1);
}

void	ft_puthex_maj_fd(long n, int fd)
{
	static char		base[16] = "0123456789ABCDEF";
	int				c;
	long			nb;

	if (n < 0)
	{
		write(fd, "-", 1);
		nb = -(long)n;
	}
	else
		nb = n;
	if ((nb / 16) > 0)
		ft_puthex_maj_fd((nb / 16), fd);
	c = (nb % 16);
	write(fd, &base[c], 1);
}

void	ft_putpointer_xmin_fd(void *p, int fd)
{
	unsigned long	add;

	add = (unsigned long)p;
	write(fd, "0x", 2);
	ft_puthex_min_fd(add, fd);
}

void	ft_putpointer_xmaj_fd(void *p, int fd)
{
	unsigned long	add;

	add = (unsigned long)p;
	write(fd, "0X", 2);
	ft_puthex_min_fd(add, fd);
}
