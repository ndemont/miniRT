/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 10:21:19 by ndemont           #+#    #+#             */
/*   Updated: 2021/02/10 14:52:33 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"

char	*free_split(char **split, char *error)
{
	int i;

	i = 0;
	if (!split)
		return (error);
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (error);
}

char	*free_parsing(char *content)
{
	if (content)
		free(content);
	return (0);
}

int		free_scene(char **split, t_scene *s)
{
	if (split)
		free_split(split, "Error");
	if (s->lights)
		free(s->lights);
	if (s->cameras)
		free(s->cameras);
	if (s->objects)
		free(s->objects);
	if (s->images)
		free(s->images);
	return (0);
}
