/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 13:29:48 by ndemont           #+#    #+#             */
/*   Updated: 2020/12/01 18:47:02 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "libft.h"

int			ft_get_conversion(va_list ap, t_printf *elem)
{
	int len;

	if (!ft_check_conversion(elem, ap))
		return (0);
	len = ft_select_conversion(ap, elem);
	return (len);
}

static int	print_conversion(const char *s, int *i, int *start, va_list ap)
{
	t_printf	elem;
	int			count;
	char		*str;
	int			len;

	len = 0;
	ft_init_elem(&elem);
	count = ft_set_elem(&s[*i], &elem);
	if (count > 0)
	{
		if (!(str = ft_substr(&s[*start], 0, *i - *start)))
			return (-1);
		ft_putstr_fd(str, 1);
		free(str);
		len = ft_get_conversion(ap, &elem);
		len = len + (*i - *start);
		*i = *i + count + 1;
		*start = *i;
	}
	else
		*i = *i + 1;
	return (len);
}

static int	print_last(const char *s, int *i, int start)
{
	char		*str;

	*i = *i + 1;
	if (s[*i] == '\0')
	{
		if (!(str = ft_substr(&s[start], 0, *i - start)))
			return (-1);
		ft_putstr_fd(str, 1);
		free(str);
		return (*i - start);
	}
	else
		return (0);
}

int			ft_printf(const char *s, ...)
{
	va_list		ap;
	int			start;
	int			i;
	int			len;

	va_start(ap, s);
	i = 0;
	len = 0;
	start = i;
	while (s[i])
	{
		if (s[i] == '%')
		{
			if ((len += print_conversion(s, &i, &start, ap)) < 0)
				return (-1);
		}
		else
		{
			if ((len += print_last(s, &i, start)) < 0)
				return (-1);
		}
	}
	va_end(ap);
	return (len);
}
