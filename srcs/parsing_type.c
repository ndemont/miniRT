/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 13:19:18 by ndemont           #+#    #+#             */
/*   Updated: 2021/01/12 15:48:00 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		parsing_r2(char **line, t_scene *elem)
{
	elem->R[0] = ft_atof(line[1]);
	elem->R[1] = ft_atof(line[2]);
}

void		parsing_a2(char **line, t_scene *elem)
{
	char	**split;

	elem->A.i = ft_atof(line[1]);
	split = ft_split(line[2], ',');
	elem->A.color.coord[0] = ft_atof(split[0]);
	elem->A.color.coord[1] = ft_atof(split[1]);
	elem->A.color.coord[2] = ft_atof(split[2]);
}

void		parsing_c2(char **line, t_scene *elem)
{
	char	**split;
	int		i;

	i = 0;
	while (elem->cameras[i].f)
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
}

void		parsing_l2(char **line, t_scene *elem)
{
	char	**split;
	int		i;

	i = 0;
	while (elem->lights[i].i)
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
}

void		parsing_pl2(char **line, t_scene *elem)
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
}

void		parsing_sp2(char **line, t_scene *elem)
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
}

void		parsing_sq2(char **line, t_scene *elem)
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
}

void		parsing_cy2(char **line, t_scene *elem)
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
	elem->objects[i].diam = ft_atof(line[3]);
	elem->objects[i].h = ft_atof(line[4]);
	split = ft_split(line[5], ',');
	elem->objects[i].c.coord[0] = ft_atof(split[0]);
	elem->objects[i].c.coord[1] = ft_atof(split[1]);
	elem->objects[i].c.coord[2] = ft_atof(split[2]);
}

void		parsing_tr2(char **line, t_scene *elem)
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
}