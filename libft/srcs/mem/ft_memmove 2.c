/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 18:43:01 by ndemont           #+#    #+#             */
/*   Updated: 2020/11/16 14:39:53 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*dst2;
	unsigned char	*src2;

	if (!src && !dst)
		return (dst);
	dst2 = (unsigned char*)dst;
	src2 = (unsigned char*)src;
	if ((long)src < (long)dst)
	{
		i = len - 1;
		while (i < len)
		{
			dst2[i] = src2[i];
			i--;
		}
	}
	else
	{
		i = -1;
		while (++i < len)
			dst2[i] = src2[i];
	}
	return (dst);
}
