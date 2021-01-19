/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 19:07:28 by ndemont           #+#    #+#             */
/*   Updated: 2020/11/16 11:45:35 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_charset(char const *set, char c)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

static int	ft_count_len(char const *s1, char const *set)
{
	int	begin;
	int	end;
	int	count;

	begin = 0;
	end = ft_strlen(s1);
	while (ft_is_charset(set, s1[begin]))
		begin++;
	while (ft_is_charset(set, s1[end - 1]) && end > 0)
		end--;
	count = 0;
	while (begin < end)
	{
		count++;
		begin++;
	}
	return (count);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		count;
	char	*trim;

	if (!s1)
		return (0);
	count = ft_count_len(s1, set);
	if (!(trim = malloc(sizeof(char) * (count + 1))))
		return (0);
	i = 0;
	while (ft_is_charset(set, *s1) && *s1)
		s1++;
	while (i < count && *s1)
	{
		trim[i] = *s1;
		s1++;
		i++;
	}
	trim[i] = '\0';
	return (trim);
}
