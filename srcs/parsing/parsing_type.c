/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 13:19:18 by ndemont           #+#    #+#             */
/*   Updated: 2021/02/03 16:54:01 by ndemont          ###   ########.fr       */
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
	if (!str[i])
		return (0);
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
	if (!str[i])
		return (0);
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
	char 	*error;

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

char		*parsing_sp(char **line, t_scene *elem)
{
	char	*error;
	int		i;

	if (line[4])
		return ("Sphere: too many arguments.\n");
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
		return ("Cylinder: too many arguments.\n");
	i = 0;
	while (elem->objects[i].type != -1)
		i++;
	elem->objects[i].type = 6;
	elem->objects[i + 1].type = -1;
	if ((error = ft_check_coord(line[1], elem->objects[i].o.coord)))
		return (error);
	if ((error = ft_check_coord(line[2], elem->objects[i].d.coord)))
		return (error);
	if (!ft_strisfloat(line[3]))
		return ("Cylinder: diameter must be a float.\n");
	elem->objects[i].diam = ft_atof(line[3]) / 2;
	if (!ft_strisfloat(line[3]))
		return ("Cylinder: height must be a float.\n");
	elem->objects[i].h = ft_atof(line[4]);
	if ((error = ft_check_color(line[5], elem->objects[i].c.coord)))
		return (error);
	return (0);

}

char		*parsing_tr(char **line, t_scene *elem)
{
	char	*error;
	int		i;

	if (line[5])
		return ("Triangle: too many arguments.\n");
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
