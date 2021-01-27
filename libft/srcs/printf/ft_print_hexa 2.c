/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 16:56:26 by ndemont           #+#    #+#             */
/*   Updated: 2020/12/01 17:42:34 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "libft.h"

void	ft_set_flags_conv_u(t_printf *elem, int *len, int *width, int *prec)
{
	*prec = *len - elem->flags.hash;
	*width = *len;
	if (elem->precision.value > *len - elem->flags.hash)
		*prec = elem->precision.value;
	if (elem->width.value > *len)
		*width = elem->width.value;
	if (*prec + elem->flags.hash > *width)
		*width = *prec + elem->flags.hash;
	if (elem->flags.zero && !elem->precision.period && !elem->flags.minus)
		*prec = *width - elem->flags.hash;
}

int		ft_puthex_min_conv(va_list ap, t_printf *elem)
{
	int				len;
	int				precision;
	int				width;
	unsigned int	n;

	n = va_arg(ap, int);
	if (!n)
		elem->flags.hash = 0;
	len = ft_intlen(16, n) + elem->flags.hash;
	if (!n && elem->precision.period)
		len = 0;
	ft_set_flags_conv_u(elem, &len, &width, &precision);
	if (elem->flags.minus == 0)
		ft_putchar_n_fd(' ', (width - precision - elem->flags.hash));
	if (elem->flags.hash && n)
		ft_putstr_fd("0x", 1);
	ft_putchar_n_fd('0', (precision - (len - elem->flags.hash)));
	if (len)
		ft_puthex_min_fd(n, 1);
	if (elem->flags.minus == 1)
		ft_putchar_n_fd(' ', (width - precision - elem->flags.hash));
	return (width);
}

int		ft_puthex_maj_conv(va_list ap, t_printf *elem)
{
	int				len;
	int				precision;
	int				width;
	unsigned int	n;

	n = va_arg(ap, int);
	if (!n)
		elem->flags.hash = 0;
	len = ft_intlen(16, n) + elem->flags.hash;
	if (!n && elem->precision.period)
		len = 0;
	ft_set_flags_conv_u(elem, &len, &width, &precision);
	if (elem->flags.minus == 0)
		ft_putchar_n_fd(' ', (width - precision - elem->flags.hash));
	if (elem->flags.hash && n)
		ft_putstr_fd("0X", 1);
	ft_putchar_n_fd('0', (precision - (len - elem->flags.hash)));
	if (len)
		ft_puthex_maj_fd(n, 1);
	if (elem->flags.minus == 1)
		ft_putchar_n_fd(' ', (width - precision - elem->flags.hash));
	return (width);
}

int		ft_putpointer_conv(va_list ap, t_printf *elem)
{
	void	*p;
	int		width;
	int		len;

	p = va_arg(ap, void *);
	len = 2 + ft_intlen(16, (long)p);
	if (!p && elem->precision.period)
		len = 2;
	width = len;
	if (elem->width.num == 1 && elem->width.value > len)
		width = elem->width.value;
	if (elem->flags.minus == 0)
		ft_putchar_n_fd(' ', (width - len));
	ft_putstr_fd("0x", 1);
	if (len != 2)
		ft_puthex_min_fd((long)p, 1);
	if (elem->flags.minus == 1)
		ft_putchar_n_fd(' ', (width - len));
	return (width);
}
