/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_elem.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 17:02:56 by ndemont           #+#    #+#             */
/*   Updated: 2020/11/29 20:48:10 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int		ft_check_flags(const char *s, t_printf *elem, int i)
{
	int	check;

	check = ft_set_flags(s[i], elem);
	while (check > 0 && s[i])
	{
		i++;
		check = ft_set_flags(s[i], elem);
	}
	return (i);
}

int		ft_check_width(const char *s, t_printf *elem, int i)
{
	int	check;

	check = ft_set_field(s[i], elem);
	while (check > 0 && s[i])
	{
		i++;
		check = ft_set_field(s[i], elem);
	}
	return (i);
}

int		ft_check_precision(const char *s, t_printf *elem, int i)
{
	int	check;

	check = ft_set_precision(s[i], elem);
	while (check > 0 && s[i])
	{
		i++;
		check = ft_set_precision(s[i], elem);
	}
	return (i);
}

int		ft_check_type(const char *s, t_printf *elem, int i)
{
	int	check;

	check = ft_set_type(s[i], elem);
	if (check == 0 || !s[i])
		return (0);
	return (i);
}

int		ft_set_elem(const char *s, t_printf *elem)
{
	int	i;

	i = 1;
	i = ft_check_flags(s, elem, i);
	i = ft_check_width(s, elem, i);
	i = ft_check_precision(s, elem, i);
	if ((i = ft_check_type(s, elem, i)) == 0)
		return (0);
	return (i);
}
