/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 18:33:20 by ndemont           #+#    #+#             */
/*   Updated: 2020/11/16 11:46:53 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbr_len(int n)
{
	int		count;
	long	nb;

	count = 0;
	if (n < 0)
	{
		nb = -(long)n;
		count++;
	}
	else
		nb = n;
	while ((nb / 10) > 0)
	{
		count++;
		nb = nb / 10;
	}
	count++;
	return (count);
}

char		*ft_itoa(int n)
{
	char	*nbr;
	long	nb;
	int		i;

	i = ft_nbr_len(n);
	if (!(nbr = malloc(sizeof(char) * (i + 1))))
		return (0);
	nbr[i] = '\0';
	i--;
	if (n < 0)
	{
		nbr[0] = '-';
		nb = -(long)n;
	}
	else
		nb = n;
	while ((nb / 10) > 0)
	{
		nbr[i] = (nb % 10) + 48;
		nb = nb / 10;
		i--;
	}
	nbr[i] = (nb % 10) + 48;
	return (nbr);
}
