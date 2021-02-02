/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 13:19:18 by ndemont           #+#    #+#             */
/*   Updated: 2021/02/02 15:55:36 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			ft_strisfloat(char *str)
{
	int i;

	i = 0;
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] == '.')
		i++;
	while (ft_isdigit(str[i]))
		i++;
	if (str[i])
		return (0);
	return (1);
}

int			ft_strisdigit(char *str)
{
	int i;

	i = 0;
	while (ft_isdigit(str[i]))
		i++;
	if (str[i])
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
char		*parsing_r(char **line, t_scene *elem)
{
	int i;

	i = 0;
	while (i < 3)
	{
		if (!ft_strisfloat(line[1]))
			return ("Resolution: value must be digital.\n");
		i++;
	}
	if (line[i])
		return ("Resolution: too many arguments.\n");
	elem->R[0] = ft_atof(line[1]);
	elem->R[1] = ft_atof(line[2]);
	if ((int)(elem->R[0]) <= 0 || (int)(elem->R[1]) <= 0)
		return ("Resolution: value can not be negative.\n");
	// if (elem->R[0] > width_max)
	// 	elem->R[0] = width_max;
	// if (elem->R[1] > height_max)
	// 	elem->R[1] = height_max;
	return (0);
}

char		*parsing_a(char **line, t_scene *elem)
{
	char	**split;
	int		i;

	if (!ft_strisfloat(line[1]))
		return ("Ambiant light: value must be digital.\n");
	elem->A.i = ft_atof(line[1]);
	if (!(ft_count_coma(line[2])))
		return ("Ambiant light: wrong arguments format");
	split = ft_split(line[2], ',');
	i = 0;
	while (i < 3)
	{
		if (!ft_strisdigit(split[i]))
			return ("Ambiant light: color values must be digital.");
		elem->A.color.coord[i] = ft_atof(split[i]);
		if ((int)elem->A.color.coord[i] < 0 || (int)elem->A.color.coord[i] > 255)
			return ("Ambiant light: color values must ∈ [0;255]");
		i++;
	}
	if (line[3] || split[i])
		return ("Ambiant light: too many arguments.");
	return (0);
}

char		*parsing_c(char **line, t_scene *elem)
{
	char	**split;
	int		i;

	i = 0;
	while (elem->cameras[i].f != -1)
		i++;
	split = ft_split(line[1], ',');
	elem->cameras[i].o.coord[0] = ft_atof(split[0]);
	elem->cameras[i].o.coord[1] = ft_atof(split[1]);
	elem->cameras[i].o.coord[2] = ft_atof(split[2]);
	split = ft_split(line[2], ',');
	elem->cameras[i].c.coord[0] = ft_atof(split[0]);
	elem->cameras[i].c.coord[1] = ft_atof(split[1]);
	elem->cameras[i].c.coord[2] = ft_atof(split[2]);
	elem->cameras[i].f = ft_atof(line[3]) * (M_PI / 180);
	i++;
	elem->cameras[i].f = -1;
	return (0);
}

char		*parsing_l(char **line, t_scene *elem)
{
	char	**split;
	int		i;

	i = 0;
	while (elem->lights[i].i != -1)
		i++;
	split = ft_split(line[1], ',');
	elem->lights[i].o.coord[0] = ft_atof(split[0]);
	elem->lights[i].o.coord[1] = ft_atof(split[1]);
	elem->lights[i].o.coord[2] = ft_atof(split[2]);
	elem->lights[i].i = ft_atof(line[2]);
	split = ft_split(line[3], ',');
	elem->lights[i].c.coord[0] = ft_atof(split[0]);
	elem->lights[i].c.coord[1] = ft_atof(split[1]);
	elem->lights[i].c.coord[2] = ft_atof(split[2]);
	i++;
	elem->lights[i].i = -1;
	return (0);

}

char		*parsing_pl(char **line, t_scene *elem)
{
	char	**split;
	int		i;

	i = 0;
	while (elem->objects[i].type != -1)
		i++;
	elem->objects[i].type = 12;
	elem->objects[i + 1].type = -1;
	split = ft_split(line[1], ',');
	elem->objects[i].o.coord[0] = ft_atof(split[0]);
	elem->objects[i].o.coord[1] = ft_atof(split[1]);
	elem->objects[i].o.coord[2] = ft_atof(split[2]);
	split = ft_split(line[2], ',');
	elem->objects[i].d.coord[0] = ft_atof(split[0]);
	elem->objects[i].d.coord[1] = ft_atof(split[1]);
	elem->objects[i].d.coord[2] = ft_atof(split[2]);
	split = ft_split(line[3], ',');
	elem->objects[i].c.coord[0] = ft_atof(split[0]);
	elem->objects[i].c.coord[1] = ft_atof(split[1]);
	elem->objects[i].c.coord[2] = ft_atof(split[2]);
	return (0);
}

char		*parsing_sp(char **line, t_scene *elem)
{
	char	**split;
	int		i;

	i = 0;
	while (elem->objects[i].type != -1)
		i++;
	elem->objects[i].type = 4;
	elem->objects[i + 1].type = -1;
	split = ft_split(line[1], ',');
	elem->objects[i].o.coord[0] = ft_atof(split[0]);
	elem->objects[i].o.coord[1] = ft_atof(split[1]);
	elem->objects[i].o.coord[2] = ft_atof(split[2]);
	elem->objects[i].diam = ft_atof(line[2]) / 2;
	split = ft_split(line[3], ',');
	elem->objects[i].c.coord[0] = ft_atof(split[0]);
	elem->objects[i].c.coord[1] = ft_atof(split[1]);
	elem->objects[i].c.coord[2] = ft_atof(split[2]);
	return (0);
}

char		*parsing_sq(char **line, t_scene *elem)
{
	char	**split;
	int		i;

	i = 0;
	while (elem->objects[i].type != -1)
		i++;
	elem->objects[i].type = 6;
	elem->objects[i + 1].type = -1;
	split = ft_split(line[1], ',');
	elem->objects[i].o.coord[0] = ft_atof(split[0]);
	elem->objects[i].o.coord[1] = ft_atof(split[1]);
	elem->objects[i].o.coord[2] = ft_atof(split[2]);
	split = ft_split(line[2], ',');
	elem->objects[i].d.coord[0] = ft_atof(split[0]);
	elem->objects[i].d.coord[1] = ft_atof(split[1]);
	elem->objects[i].d.coord[2] = ft_atof(split[2]);
	elem->objects[i].h = ft_atof(line[3]);
	split = ft_split(line[4], ',');
	elem->objects[i].c.coord[0] = ft_atof(split[0]);
	elem->objects[i].c.coord[1] = ft_atof(split[1]);
	elem->objects[i].c.coord[2] = ft_atof(split[2]);
	return (0);
}

char		*parsing_cy(char **line, t_scene *elem)
{
	char	**split;
	int		i;

	i = 0;
	while (elem->objects[i].type != -1)
		i++;
	elem->objects[i].type = 8;
	elem->objects[i + 1].type = -1;
	split = ft_split(line[1], ',');
	elem->objects[i].o.coord[0] = ft_atof(split[0]);
	elem->objects[i].o.coord[1] = ft_atof(split[1]);
	elem->objects[i].o.coord[2] = ft_atof(split[2]);
	split = ft_split(line[2], ',');
	elem->objects[i].d.coord[0] = ft_atof(split[0]);
	elem->objects[i].d.coord[1] = ft_atof(split[1]);
	elem->objects[i].d.coord[2] = ft_atof(split[2]);
	elem->objects[i].diam = ft_atof(line[3]) / 2;
	elem->objects[i].h = ft_atof(line[4]);
	split = ft_split(line[5], ',');
	elem->objects[i].c.coord[0] = ft_atof(split[0]);
	elem->objects[i].c.coord[1] = ft_atof(split[1]);
	elem->objects[i].c.coord[2] = ft_atof(split[2]);
	return (0);

}

char		*parsing_tr(char **line, t_scene *elem)
{
	char	**split;
	int		i;

	i = 0;
	while (elem->objects[i].type != -1)
		i++;
	elem->objects[i].type = 10;
	elem->objects[i + 1].type = -1;
	split = ft_split(line[1], ',');
	elem->objects[i].o.coord[0] = ft_atof(split[0]);
	elem->objects[i].o.coord[1] = ft_atof(split[1]);
	elem->objects[i].o.coord[2] = ft_atof(split[2]);
	split = ft_split(line[2], ',');
	elem->objects[i].d.coord[0] = ft_atof(split[0]);
	elem->objects[i].d.coord[1] = ft_atof(split[1]);
	elem->objects[i].d.coord[2] = ft_atof(split[2]);
	split = ft_split(line[3], ',');
	elem->objects[i].p.coord[0] = ft_atof(split[0]);
	elem->objects[i].p.coord[1] = ft_atof(split[1]);
	elem->objects[i].p.coord[2] = ft_atof(split[2]);
	split = ft_split(line[4], ',');
	elem->objects[i].c.coord[0] = ft_atof(split[0]);
	elem->objects[i].c.coord[1] = ft_atof(split[1]);
	elem->objects[i].c.coord[2] = ft_atof(split[2]);
	elem->objects[i].t1 = elem->objects[i].o;
	elem->objects[i].t2 = elem->objects[i].d;
	elem->objects[i].t3 = elem->objects[i].p;
	return (0);
}
