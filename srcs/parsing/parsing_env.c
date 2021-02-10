/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 20:32:05 by ndemont           #+#    #+#             */
/*   Updated: 2021/02/10 17:22:39 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"

int		init_scene(t_scene *s, char **list)
{
	int c;
	int l;
	int o;

	ft_count_elem(list, &c, &l, &o);
	if (!(s->lights = malloc(sizeof(t_light) * (l + 1))))
		return (0);
	s->lights[0].i = -1;
	if (!(s->cameras = malloc(sizeof(t_camera) * (c + 1))))
		return (0);
	s->cameras[0].f = -1;
	s->cam_nbr = c;
	if (!(s->objects = malloc(sizeof(t_object) * (o + 1))))
		return (0);
	s->objects[0].type = -1;
	s->a.i = 0;
	return (1);
}

char	*parsing_r(char **line, t_scene *elem)
{
	if (!line[1] || !line[2])
		return ("Error 8: Resolution - missing argument.");
	if (!ft_strisfloat(line[1]))
		return ("Error 10: Resolution - value must be digital.");
	if (!ft_strisfloat(line[2]))
		return ("Error 10: Resolution: value must be digital.");
	if (elem->r[0] || elem->r[1])
		return ("Resolution: too many resolution.");
	elem->r[0] = ft_atof(line[1]);
	elem->r[1] = ft_atof(line[2]);
	if ((int)(elem->r[0]) <= 0 || (int)(elem->r[1]) <= 0)
		return ("Error 9: Resolution - value can not be negative.");
	if (line[3])
		return ("Resolution: too many arguments.");
	return (0);
}

char	*parsing_a(char **line, t_scene *elem)
{
	char	*error;

	if (!line[1] || !line[2])
		return ("Ambiant light: Missing argument.");
	if (!ft_strisfloat(line[1]))
		return ("Ambiant light: value must be digital.");
	if (elem->a.i < 0)
		return ("Ambiant light: too many ambiant lights.");
	elem->a.i = ft_atof(line[1]);
	if ((error = ft_check_color(line[2], elem->a.color.coord)))
		return (error);
	if (line[3])
		return ("Ambiant light: too many arguments.");
	return (0);
}

char	*parsing_c(char **line, t_scene *elem)
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

char	*parsing_l(char **line, t_scene *elem)
{
	char	*error;
	int		i;

	if (line[4])
		return ("Light: wrong numbers of arguments.\n");
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
