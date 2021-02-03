/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 13:19:18 by ndemont           #+#    #+#             */
/*   Updated: 2021/02/03 13:13:17 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char 		*leaks(char **split, char *error)
{
	int i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (error);
}

int			ft_strisfloat(char *str)
{
	int i;

	i = 0;
	if (str[i] == '-')
		i++;
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

char		*ft_check_coord(char *line, float c[3])
{
	char	**split;
	int 	i;

	if (!(ft_count_coma(line)))
		return ("Wrong arguments format");
	split = ft_split(line, ',');
	i = 0;
	while (i < 3)
	{
		if (ft_strisfloat(split[i]))
			c[i] = ft_atof(split[i]);
		else
			return (leaks(split, "Color value must be float"));
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
			c[i]= ft_atof(split[i]);
		else 
			return (leaks(split, "Color value must be integer"));
		i++;
	}
	if (split[3])
		return (leaks(split, "Wrong number of color arguments"));
	if (c[0] < 0 || c[1] < 0 || c[2] < 0 || c[0] > 255 || c[1] > 255 || c[2] > 255)
		return (leaks(split, "Color values must ∈ [0;255]"));
	return (leaks(split, 0));
}

char		*parsing_r(char **line, t_scene *elem)
{
	int i;

	i = 1;
	while (i < 3)
	{
		if (!ft_strisfloat(line[i]))
			return ("Resolution: value must be digital.\n");
		i++;
	}
	if (line[3])
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
	char 	*error;
	int		i;

	if (!ft_strisfloat(line[1]))
		return ("Ambiant light: value must be digital.\n");
	elem->A.i = ft_atof(line[1]);
	if (!(ft_count_coma(line[2])))
		return ("Ambiant light: wrong arguments format");
	i = 0;
	if ((error = ft_check_color(line[2], elem->A.color.coord)))
			return (error);
	if (line[3])
		return ("Ambiant light: too many arguments.");
	return (0);
}

char		*parsing_c(char **line, t_scene *elem)
{
	//char	**split;
	char	*error;
	int		i;

	if (line[4])
		return ("Camera: too many arguments.\n");
	i = 0;
	while (elem->cameras[i].f != -1)
		i++;
	if ((error = ft_check_coord(line[1], elem->cameras[i].o.coord)))
		return (error);
	if ((error = ft_check_coord(line[2], elem->cameras[i].c.coord)))
		return (error);
	elem->cameras[i].f = ft_atof(line[3]) * (M_PI / 180);
	i++;
	elem->cameras[i].f = -1;
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
	elem->lights[i].i = ft_atof(line[2]);
	if ((error = ft_check_coord(line[3], elem->lights[i].c.coord)))
		return (error);
	i++;
	elem->lights[i].i = -1;
	return (0);
}

char		*parsing_pl(char **line, t_scene *elem)
{
	char	**split;
	int		i;

	i = 0;
	if (line[4])
		return ("Plan: too many arguments.\n");
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

	if (line[4])
		return ("Sphere: too many arguments.\n");
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
	if (line[5])
		return ("Square: too many arguments.\n");
	while (elem->objects[i].type != -1)
		i++;
	elem->objects[i].type = 5;
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

	if (line[6])
		return ("Cylinder: too many arguments.\n");
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

	if (line[5])
		return ("Triangle: too many arguments.\n");
	i = 0;
	while (elem->objects[i].type != -1)
		i++;
	elem->objects[i].type = 7;
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
