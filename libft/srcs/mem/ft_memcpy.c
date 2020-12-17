/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 19:04:16 by ndemont           #+#    #+#             */
/*   Updated: 2020/11/16 11:58:20 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*cpy;
	size_t	i;

	cpy = dst;
	i = 0;
	if (!src && !dst)
		return (dst);
	while (i < n)
	{
		cpy[i] = *(char*)src;
		i++;
		src++;
	}
	return (dst);
}
