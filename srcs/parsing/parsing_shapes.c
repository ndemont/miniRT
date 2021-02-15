/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_shapes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 20:25:52 by ndemont           #+#    #+#             */
/*   Updated: 2021/02/15 12:49:43 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"

char		*parsing_sp(char **line, t_scene *elem)
{
	char	*error;
	int		i;

	if (line[4])
		return ("Sphere: wrong numbers of arguments.\n");
	i = 0;
	while (elem->objects[i].type != -1)
		i++;
	elem->objects[i].type = 4;
	elem->objects[i + 1].type = -1;
	if ((error = ft_check_coord(line[1], elem->objects[i].o.coord)))
		return (error);
	if (!ft_strisfloat(line[2]))
		return ("Sphere: diameter must be a float.\n");
	elem->objects[i].diam = ft_atof(line[2]) / 2;
	if ((error = ft_check_color(line[3], elem->objects[i].c.coord)))
		return (error);
	return (0);
}

char		*parsing_st(char **line, t_scene *elem)
{
	char	*error;
	int		i;

	if (line[6])
		return ("Sphere: wrong numbers of arguments.\n");
	i = 0;
	while (elem->objects[i].type != -1)
		i++;
	elem->objects[i].type = 10;
	elem->objects[i + 1].type = -1;
	if ((error = ft_check_coord(line[1], elem->objects[i].o.coord)))
		return (error);
	if (!ft_strisfloat(line[2]))
		return ("Sphere: diameter must be a float.\n");
	elem->objects[i].diam = ft_atof(line[2]) / 2;
	if ((error = ft_check_color(line[3], elem->objects[i].t1.coord)))
		return (error);
	if ((error = ft_check_color(line[4], elem->objects[i].t2.coord)))
		return (error);
	elem->objects[i].h = ft_atof(line[5]);
	if (!ft_strisfloat(line[5]))
		return ("Sphere: diameter must be a float.\n");
	return (0);
}

char		*parsing_cl(char **line, t_scene *elem)
{
	char	*error;
	int		i;

	if (line[5])
		return ("Circle: wrong numbers of arguments.\n");
	i = 0;
	while (elem->objects[i].type != -1)
		i++;
	elem->objects[i].type = 9;
	elem->objects[i + 1].type = -1;
	if ((error = ft_check_coord(line[1], elem->objects[i].o.coord)))
		return (error);
	if ((error = ft_check_coord(line[2], elem->objects[i].d.coord)))
		return (error);
	if (!ft_strisfloat(line[3]))
		return ("Circle: diameter must be a float.\n");
	elem->objects[i].diam = ft_atof(line[3]) / 2;
	if ((error = ft_check_color(line[4], elem->objects[i].c.coord)))
		return (error);
	return (0);
}

char		*parsing_sq(char **line, t_scene *elem)
{
	char	*error;
	int		i;

	i = 0;
	if (!line[1] || !line[2] || !line[3] || !line[4])
		return ("Square: Missing argument.\n");
	if (line[5])
		return ("Square: too many arguments.\n");
	while (elem->objects[i].type != -1)
		i++;
	elem->objects[i].type = 5;
	elem->objects[i + 1].type = -1;
	if ((error = ft_check_coord(line[1], elem->objects[i].o.coord)))
		return (error);
	if ((error = ft_check_coord(line[2], elem->objects[i].d.coord)))
		return (error);
	if (!ft_strisfloat(line[3]))
		return ("Square: height must be a float.\n");
	elem->objects[i].h = ft_atof(line[3]);
	if ((error = ft_check_color(line[4], elem->objects[i].c.coord)))
		return (error);
	return (0);
}

char		*parsing_cy(char **line, t_scene *elem)
{
	char	*error;
	int		i;

	if (line[6])
		return ("Cylinder: wrong numbers of argumetns.");
	i = 0;
	while (elem->objects[i].type != -1)
		i++;
	elem->objects[i].type = 6;
	elem->objects[i + 1].type = -1;
	if ((error = ft_check_coord(line[1], elem->objects[i].o.coord)))
		return (error);
	if ((error = ft_check_coord(line[2], elem->objects[i].d.coord)))
		return (error);
	if ((error = ft_check_color(line[3], elem->objects[i].c.coord)))
		return (error);
	if (!ft_strisfloat(line[4]))
		return ("Cylinder: diameter must be a float.");
	elem->objects[i].diam = ft_atof(line[4]) / 2;
	if (!ft_strisfloat(line[5]))
		return ("Cylinder: height must be a float.");
	elem->objects[i].h = ft_atof(line[5]);
	return (0);
}

char		*parsing_tr(char **line, t_scene *elem)
{
	char	*error;
	int		i;

	if (line[5])
		return ("Triangle: wrong numbers of arguments.");
	i = 0;
	while (elem->objects[i].type != -1)
		i++;
	elem->objects[i].type = 7;
	elem->objects[i + 1].type = -1;
	if ((error = ft_check_coord(line[1], elem->objects[i].t1.coord)))
		return (error);
	if ((error = ft_check_coord(line[2], elem->objects[i].t2.coord)))
		return (error);
	if ((error = ft_check_coord(line[3], elem->objects[i].t3.coord)))
		return (error);
	if ((error = ft_check_coord(line[4], elem->objects[i].c.coord)))
		return (error);
	return (0);
}

char		*parsing_pl(char **line, t_scene *elem)
{
	char	*error;
	int		i;

	i = 0;
	if (line[4])
		return ("Plan: too many arguments.\n");
	while (elem->objects[i].type != -1)
		i++;
	elem->objects[i].type = 8;
	elem->objects[i + 1].type = -1;
	if ((error = ft_check_coord(line[1], elem->objects[i].o.coord)))
		return (error);
	if ((error = ft_check_coord(line[2], elem->objects[i].d.coord)))
		return (error);
	if ((error = ft_check_color(line[3], elem->objects[i].c.coord)))
		return (error);
	return (0);
}
