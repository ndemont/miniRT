/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_chars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 16:56:26 by ndemont           #+#    #+#             */
/*   Updated: 2020/12/01 18:54:46 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "libft.h"

int		ft_putstr_conv(va_list ap, t_printf *elem)
{
	int		width;
	int		prec;
	int		l;
	char	*str;

	str = va_arg(ap, char *);
	if (!str)
		str = "(null)";
	l = ft_strlen(str);
	prec = ft_strlen(str);
	width = 0;
	if (elem->precision.period && elem->precision.value < l)
		prec = elem->precision.value;
	if (elem->width.num && (elem->width.value > l || elem->width.value > prec))
		width = elem->width.value;
	if (width < prec)
		width = prec;
	if (elem->flags.minus == 0)
		ft_putchar_n_fd(' ', (width - prec));
	write(1, str, prec);
	if (elem->flags.minus == 1)
		ft_putchar_n_fd(' ', (width - prec));
	return (width);
}

int		ft_putchar_conv(va_list ap, t_printf *elem)
{
	int		len;

	len = 1;
	if (elem->width.num == 1 && elem->width.value > 0)
		len = elem->width.value;
	if (elem->flags.minus == 1)
	{
		ft_putchar_fd(va_arg(ap, int), 1);
		ft_putchar_n_fd(' ', len - 1);
	}
	else
	{
		ft_putchar_n_fd(' ', len - 1);
		ft_putchar_fd(va_arg(ap, int), 1);
	}
	return (len);
}

int		ft_putper_conv(va_list ap, t_printf *elem)
{
	int		len;
	char	c;

	c = ' ';
	len = 1;
	(void)ap;
	if (elem->width.num == 1 && elem->width.value > 0)
		len = elem->width.value;
	if (elem->flags.zero)
		c = '0';
	if (elem->flags.minus == 1)
	{
		ft_putchar_fd('%', 1);
		ft_putchar_n_fd(' ', len - 1);
	}
	else
	{
		ft_putchar_n_fd(c, len - 1);
		ft_putchar_fd('%', 1);
	}
	return (len);
}
