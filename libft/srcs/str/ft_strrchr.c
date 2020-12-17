/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 19:34:58 by ndemont           #+#    #+#             */
/*   Updated: 2020/11/16 11:37:33 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	count;

	count = 0;
	while (*(char*)s != '\0')
	{
		s++;
		count++;
	}
	while (count >= 0)
	{
		if (c == *(char*)s)
			return ((char*)s);
		count--;
		s--;
	}
	return (NULL);
}
