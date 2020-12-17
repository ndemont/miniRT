/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 19:20:41 by ndemont           #+#    #+#             */
/*   Updated: 2020/11/17 17:29:23 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_count_strlen(const char *s, char c)
{
	int	count;

	count = 0;
	while (s[count] != c && s[count])
		count++;
	return (count);
}

static int			ft_count_splitlen(const char *s, char c)
{
	int	count;

	count = 0;
	s++;
	while (*(s - 1) && *s)
	{
		if (*s == c && *(s - 1) != c)
			count++;
		s++;
	}
	if (*(s - 1) && *(s - 1) != c)
		count++;
	return (count);
}

static const char	*ft_dup_split(char **split, int i, const char *s, char c)
{
	int j;

	if (!(split[i] = malloc(sizeof(char) * (ft_count_strlen(s, c) + 1))))
		return (0);
	j = 0;
	while (*s != c && *s)
	{
		split[i][j] = *s;
		j++;
		s++;
	}
	split[i][j] = '\0';
	return (s);
}

char				**ft_split(char const *s, char c)
{
	char	**split;
	int		count;
	int		i;

	if (!s)
		return (NULL);
	count = ft_count_splitlen((char*)s, c);
	if (!(split = malloc(sizeof(char*) * (count + 1))))
		return (0);
	split[count] = 0;
	i = 0;
	while (i < count && *s)
	{
		if (*s != c)
		{
			if (!(s = ft_dup_split(split, i, s, c)))
				return (NULL);
			i++;
		}
		else
			s++;
	}
	return (split);
}
