/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 19:45:34 by ndemont           #+#    #+#             */
/*   Updated: 2020/11/16 11:53:01 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcat(char *s1, const char *s2)
{
	int	index;
	int	index2;

	index = 0;
	index2 = 0;
	while (s1[index] != '\0')
	{
		index++;
	}
	while (s2[index2] != '\0')
	{
		s1[index] = s2[index2];
		index++;
		index2++;
	}
	s1[index] = '\0';
	return (s1);
}
