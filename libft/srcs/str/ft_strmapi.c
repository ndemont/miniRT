/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 19:26:19 by ndemont           #+#    #+#             */
/*   Updated: 2020/10/25 19:26:59 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*final;
	int		len;
	int		i;

	len = 0;
	i = 0;
	if (!s)
		return (0);
	while (s[len])
		len++;
	if (!(final = malloc(sizeof(char) * (len + 1))))
		return (0);
	while (i < len)
	{
		final[i] = (*f)(i, s[i]);
		i++;
	}
	final[i] = '\0';
	return (final);
}
