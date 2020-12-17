/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 19:39:19 by ndemont           #+#    #+#             */
/*   Updated: 2020/11/16 11:37:13 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*(char*)s != '\0')
	{
		if (c == *(char*)s)
			return ((char*)s);
		s++;
	}
	if (c == *(char*)s)
		return ((char*)s);
	else
		return (NULL);
}
