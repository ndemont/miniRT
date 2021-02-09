/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 15:04:50 by ndemont           #+#    #+#             */
/*   Updated: 2021/02/09 15:11:39 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static float	ft_convert_float(float nb, int i, const char *str)
{
	i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb + (0.1 * (str[i] - 48));
		i++;
	}
	return (nb);
}

float			ft_atof(const char *str)
{
	int		i;
	float	nb;
	float	sign;

	i = 0;
	nb = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - 48);
		i++;
	}
	if (str[i] == '.')
		nb = ft_convert_float(nb, i, str);
	return (nb * sign);
}
