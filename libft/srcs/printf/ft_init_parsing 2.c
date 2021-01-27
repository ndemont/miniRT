/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 13:01:52 by ndemont           #+#    #+#             */
/*   Updated: 2020/12/01 17:28:00 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "libft.h"

void	ft_init_flags(t_printf *elem)
{
	elem->flags.minus = 0;
	elem->flags.zero = 0;
	elem->flags.plus = 0;
	elem->flags.hash = 0;
}

void	ft_init_width(t_printf *elem)
{
	elem->width.num = 0;
	elem->width.value = 0;
	elem->width.star = 0;
}

void	ft_init_precision(t_printf *elem)
{
	elem->precision.period = 0;
	elem->precision.value = 0;
	elem->precision.star = 0;
}

void	ft_init_type(t_printf *elem)
{
	elem->type.letter = '\0';
}

void	ft_init_elem(t_printf *elem)
{
	ft_init_flags(elem);
	ft_init_width(elem);
	ft_init_precision(elem);
	ft_init_type(elem);
}
