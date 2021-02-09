/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 13:19:18 by ndemont           #+#    #+#             */
/*   Updated: 2021/02/09 10:50:59 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"

int			ft_strisfloat(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] == '-')
		i++;
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] == '.')
		i++;
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] || i == 0)
		return (0);
	return (1);
}

int			ft_strisdigit(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] || i == 0)
		return (0);
	return (1);
}

int			ft_count_coma(char *str)
{
	int i;
	int c;

	i = 0;
	c = 0;
	while (str[i])
	{
		if (str[i] == ',')
			c++;
		i++;
	}
	if (c > 2)
		return (0);
	return (1);
}

char		*ft_check_coord(char *line, float c[3])
{
	char	**split;
	int		i;

	if (!(ft_count_coma(line)))
		return ("Wrong arguments format");
	split = ft_split(line, ',');
	i = 0;
	while (i < 3)
	{
		if (ft_strisfloat(split[i]))
			c[i] = ft_atof(split[i]);
		else
			return (leaks(split, "Coordinates value must be float"));
		i++;
	}
	if (split[3])
		return (leaks(split, "Wrong number of coordinates arguments"));
	return (leaks(split, 0));
}

char		*ft_check_color(char *line, float c[3])
{
	char	**split;
	int		i;

	if (!(ft_count_coma(line)))
		return ("Wrong arguments format");
	split = ft_split(line, ',');
	i = 0;
	while (i < 3)
	{
		if (ft_strisdigit(split[i]))
			c[i] = ft_atof(split[i]);
		else
			return (leaks(split, "Color value must be integer"));
		i++;
	}
	if (split[3])
		return (leaks(split, "Wrong number of color arguments"));
	if (c[0] < 0 || c[1] < 0 || c[2] < 0 || c[0] > 255 ||
		c[1] > 255 || c[2] > 255)
		return (leaks(split, "Color values must ∈ [0;255]"));
	return (leaks(split, 0));
}
