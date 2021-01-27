/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select_conversion.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 12:43:57 by ndemont           #+#    #+#             */
/*   Updated: 2020/12/01 13:43:59 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "libft.h"

int		ft_intlen(int unit, long n)
{
	long len;

	len = 1;
	if (n < 0)
		n = -n;
	while ((n / unit) > 0)
	{
		len++;
		n = n / unit;
	}
	return (len);
}

int		ft_select_conversion(va_list ap, t_printf *elem)
{
	int len;

	len = 0;
	if (elem->type.letter == '%')
		len = ft_putper_conv(ap, elem);
	if (elem->type.letter == 'c')
		len = ft_putchar_conv(ap, elem);
	if (elem->type.letter == 's')
		len = ft_putstr_conv(ap, elem);
	if (elem->type.letter == 'i' || elem->type.letter == 'd')
		len = ft_putint_conv(ap, elem);
	if (elem->type.letter == 'u')
		len = ft_putuint_conv(ap, elem);
	if (elem->type.letter == 'p')
		len = ft_putpointer_conv(ap, elem);
	if (elem->type.letter == 'x')
		len = ft_puthex_min_conv(ap, elem);
	if (elem->type.letter == 'X')
		len = ft_puthex_maj_conv(ap, elem);
	return (len);
}
