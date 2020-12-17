/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_integer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 16:56:26 by ndemont           #+#    #+#             */
/*   Updated: 2020/12/01 17:42:32 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "libft.h"

int		ft_set_flags_conv_i(t_printf *elem, int *len, int *neg, int *precision)
{
	int width;

	*precision = *len;
	if (elem->precision.value > *len)
		*precision = elem->precision.value;
	width = *precision + *neg + elem->flags.plus;
	if (elem->width.value > (*precision + *neg + elem->flags.plus))
		width = elem->width.value;
	if (*precision > (width - *neg))
		width = *precision + *neg;
	if (elem->flags.zero && !elem->precision.period && !elem->flags.minus)
		*precision = width - *neg - elem->flags.plus;
	return (width);
}

long	ft_set_int_conv_i(va_list ap, t_printf *elem, int *neg, int *len)
{
	long n;

	n = va_arg(ap, int);
	*len = ft_intlen(10, n);
	*neg = 0;
	if (n < 0)
	{
		n = -n;
		*neg = 1;
		elem->flags.plus = 0;
	}
	if (!n && elem->precision.period)
		*len = 0;
	return (n);
}

int		ft_putint_conv(va_list ap, t_printf *elem)
{
	int		width;
	int		precision;
	int		len;
	long	n;
	int		neg;

	n = ft_set_int_conv_i(ap, elem, &neg, &len);
	width = ft_set_flags_conv_i(elem, &len, &neg, &precision);
	if (elem->flags.minus == 0)
		ft_putchar_n_fd(' ', (width - precision - neg - elem->flags.plus));
	if (neg)
		ft_putchar_fd('-', 1);
	if (elem->flags.plus)
		ft_putchar_fd('+', 1);
	ft_putchar_n_fd('0', (precision - len));
	if (len)
		ft_putnbr_fd(n, 1);
	if (elem->flags.minus == 1)
		ft_putchar_n_fd(' ', (width - precision - neg - elem->flags.plus));
	return (width);
}

int		ft_putuint_conv(va_list ap, t_printf *elem)
{
	int				len;
	int				precision;
	int				width;
	unsigned int	n;

	n = va_arg(ap, int);
	len = ft_intlen(10, n);
	if (!n && elem->precision.period)
		len = 0;
	ft_set_flags_conv_u(elem, &len, &width, &precision);
	if (elem->flags.minus == 0)
		ft_putchar_n_fd(' ', (width - precision));
	ft_putchar_n_fd('0', (precision - len));
	if (len)
		ft_putnbr_fd(n, 1);
	if (elem->flags.minus == 1)
		ft_putchar_n_fd(' ', (width - precision));
	return (width);
}
