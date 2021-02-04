/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 20:32:05 by ndemont           #+#    #+#             */
/*   Updated: 2021/02/04 20:33:48 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char		*parsing_r(char **line, t_scene *elem)
{
	if (!line[1] || !line[2])
		return ("Resolution: Missing argument.\n");
	if (!ft_strisfloat(line[1]))
		return ("Resolution: value must be digital.\n");
	if (!ft_strisfloat(line[2]))
		return ("Resolution: value must be digital.\n");
	elem->R[0] = ft_atof(line[1]);
	elem->R[1] = ft_atof(line[2]);
	if ((int)(elem->R[0]) <= 0 || (int)(elem->R[1]) <= 0)
		return ("Resolution: value can not be negative.\n");
	// if (elem->R[0] > width_max)
	// 	elem->R[0] = width_max;
	// if (elem->R[1] > height_max)
	// 	elem->R[1] = height_max;
	if (line[3])
		return ("Resolution: too many arguments.\n");
	return (0);
}

char		*parsing_a(char **line, t_scene *elem)
{
	char	*error;

	if (!line[1] || !line[2])
		return ("Ambiant light: Missing argument.\n");
	if (!ft_strisfloat(line[1]))
		return ("Ambiant light: value must be digital.\n");
	elem->A.i = ft_atof(line[1]);
	if ((error = ft_check_color(line[2], elem->A.color.coord)))
		return (error);
	if (line[3])
		return ("Ambiant light: too many arguments.");
	return (0);
}

char		*parsing_c(char **line, t_scene *elem)
{
	char	*error;
	int		i;

	i = 0;
	while (elem->cameras[i].f != -1)
		i++;
	if ((error = ft_check_coord(line[1], elem->cameras[i].o.coord)))
		return (error);
	if ((error = ft_check_coord(line[2], elem->cameras[i].c.coord)))
		return (error);
	if (!ft_strisfloat(line[3]))
		return ("Camera: focal must be float.\n");
	elem->cameras[i].f = ft_atof(line[3]) * (M_PI / 180);
	i++;
	elem->cameras[i].f = -1;
	if (line[4])
		return ("Camera: too many arguments.\n");
	return (0);
}

char		*parsing_l(char **line, t_scene *elem)
{
	char	*error;
	int		i;

	if (line[4])
		return ("Light: too many arguments.\n");
	i = 0;
	while (elem->lights[i].i != -1)
		i++;
	if ((error = ft_check_coord(line[1], elem->lights[i].o.coord)))
		return (error);
	if (!ft_strisfloat(line[2]))
		return ("Light: intensity must be float.\n");
	elem->lights[i].i = ft_atof(line[2]);
	if ((error = ft_check_coord(line[3], elem->lights[i].c.coord)))
		return (error);
	i++;
	elem->lights[i].i = -1;
	return (0);
}
