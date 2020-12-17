/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 18:41:47 by ndemont           #+#    #+#             */
/*   Updated: 2020/11/16 11:38:54 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t i;
	size_t len;

	i = 0;
	while (dst[i] && i < dstsize)
		i++;
	if (i >= dstsize)
		return (dstsize + ft_strlen(src));
	len = i;
	while (src[i - len] && i < dstsize - 1)
	{
		dst[i] = src[i - len];
		i++;
	}
	dst[i] = '\0';
	return (len + ft_strlen(src));
}
