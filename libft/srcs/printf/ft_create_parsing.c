/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 17:01:25 by ndemont           #+#    #+#             */
/*   Updated: 2020/12/01 17:27:56 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "libft.h"

int		ft_set_flags(char c, t_printf *elem)
{
	if (c == '-')
		elem->flags.minus = 1;
	else if (c == '0')
		elem->flags.zero = 1;
	else if (c == '+')
		elem->flags.plus = 1;
	else if (c == '#')
		elem->flags.hash = 2;
	else
		return (0);
	return (1);
}

int		ft_set_field(char c, t_printf *elem)
{
	if (ft_isdigit(c) && elem->width.star == 0)
	{
		elem->width.num = 1;
		elem->width.value = elem->width.value * 10 + (c - 48);
	}
	else if (c == '*' && elem->width.star == 0)
	{
		elem->width.num = 1;
		elem->width.star = 1;
	}
	else
		return (0);
	return (1);
}

int		ft_set_precision(char c, t_printf *elem)
{
	if (c == '.' && elem->precision.period == 0 && elem->precision.star == 0)
		elem->precision.period = 1;
	else if (c == '*' && elem->precision.star == 0 && \
	elem->precision.period == 1)
		elem->precision.star = 1;
	else if ((ft_isdigit(c)) && elem->precision.period == 1 && \
	elem->precision.star == 0)
		elem->precision.value = 10 * elem->precision.value + (c - 48);
	else
		return (0);
	return (1);
}

int		ft_set_type(char c, t_printf *elem)
{
	static char *tab = "%cdefginpsuxX";
	int			i;

	i = 0;
	while (tab[i])
	{
		if (c == tab[i])
		{
			elem->type.letter = c;
			return (1);
		}
		i++;
	}
	return (0);
}
