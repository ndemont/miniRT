/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 20:32:05 by ndemont           #+#    #+#             */
/*   Updated: 2021/02/12 01:03:42 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"

#if LINUX == 1

char	*parsing_r(char **line, t_scene *s)
{
	int x;
	int y;

	if (!line[1] || !line[2])
		return ("Error 8: Resolution - missing argument.");
	if (!ft_strisfloat(line[1]))
		return ("Error 10: Resolution - value must be digital.");
	if (!ft_strisfloat(line[2]))
		return ("Error 10: Resolution: value must be digital.");
	if (s->r[0] || s->r[1])
		return ("Resolution: too many resolution.");
	s->r[0] = ft_atof(line[1]);
	s->r[1] = ft_atof(line[2]);
	s->reso.width = s->r[0];
	s->reso.height = s->r[1];
	mlx_get_screen_size(s->mlx_ptr, &x, &y);
	if (s->r[0] > x)
		s->r[0] = x;
	if (s->r[1] > y)
		s->r[1] = y;
	if ((int)(s->r[0]) <= 0 || (int)(s->r[1]) <= 0)
		return ("Error 9: Resolution value has to be > 0");
	if (line[3])
		return ("Resolution: too many arguments.");
	return (0);
}

#else

char	*parsing_r(char **line, t_scene *s)
{
	if (!line[1] || !line[2])
		return ("Error 8: Resolution - missing argument.");
	if (!ft_strisfloat(line[1]))
		return ("Error 10: Resolution - value must be digital.");
	if (!ft_strisfloat(line[2]))
		return ("Error 10: Resolution: value must be digital.");
	if (s->r[0] || s->r[1])
		return ("Resolution: too many resolution.");
	s->r[0] = ft_atof(line[1]);
	s->r[1] = ft_atof(line[2]);
	s->reso.width = s->r[0];
	s->reso.height = s->r[1];
	if (s->r[0] > MAX_WIDTH_MAC)
		s->r[0] = MAX_WIDTH_MAC;
	if (s->r[1] > MAX_HEIGHT_MAC)
		s->r[1] = MAX_HEIGHT_MAC;
	if ((int)(s->r[0]) <= 0 || (int)(s->r[1]) <= 0)
		return ("Error 9: Resolution value has to be > 0");
	if (line[3])
		return ("Resolution: too many arguments.");
	return (0);
}

#endif

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
