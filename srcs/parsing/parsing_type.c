/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 13:19:18 by ndemont           #+#    #+#             */
/*   Updated: 2021/01/28 19:10:25 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		parsing_r(char **line, t_scene *elem)
{
	elem->R[0] = ft_atof(line[1]);
	elem->R[1] = ft_atof(line[2]);
}

void		parsing_a(char **line, t_scene *elem)
{
	char	**split;

	elem->A.i = ft_atof(line[1]);
	split = ft_split(line[2], ',');
	elem->A.color.coord[0] = ft_atof(split[0]);
	elem->A.color.coord[1] = ft_atof(split[1]);
	elem->A.color.coord[2] = ft_atof(split[2]);
}

void		parsing_c(char **line, t_scene *elem)
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
	printf("cam = %f/%f/%f\n", elem->cameras[0].c.coord[0], elem->cameras[0].c.coord[1], elem->cameras[0].c.coord[2]);
	elem->cameras[i].f = ft_atof(line[3]) * (M_PI / 180);
}

void		parsing_l(char **line, t_scene *elem)
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
}

void		parsing_pl(char **line, t_scene *elem)
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

void		parsing_sp(char **line, t_scene *elem)
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

void		parsing_sq(char **line, t_scene *elem)
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

void		parsing_cy(char **line, t_scene *elem)
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
}

void		parsing_tr(char **line, t_scene *elem)
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
