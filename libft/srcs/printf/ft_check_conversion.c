/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_conversion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 16:56:35 by ndemont           #+#    #+#             */
/*   Updated: 2020/12/01 17:27:49 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "libft.h"

int		ft_check_errors(t_printf *elem)
{
	char c;

	c = elem->type.letter;
	if (c == 'c' || c == 's' || c == 'p')
	{
		if (elem->flags.zero || elem->flags.hash || elem->flags.plus)
			return (0);
	}
	if (c == 'u')
		if (elem->flags.hash || elem->flags.plus)
			return (0);
	if (c == 'x' || c == 'X')
		if (elem->flags.plus)
			return (0);
	if (c == 'd' || c == 'i')
		if (elem->flags.hash)
			return (0);
	return (1);
}

int		ft_check_conversion(t_printf *elem, va_list ap)
{
	if (!ft_check_errors(elem))
		return (0);
	if (elem->flags.zero && elem->flags.minus)
		elem->flags.zero = 0;
	if (elem->width.star)
		elem->width.value = va_arg(ap, long);
	if (elem->precision.star)
		elem->precision.value = va_arg(ap, long);
	if (elem->precision.value < 0)
		elem->precision.period = 0;
	if (elem->width.value < 0)
	{
		elem->width.value = -elem->width.value;
		elem->flags.minus = 1;
	}
	return (1);
}
