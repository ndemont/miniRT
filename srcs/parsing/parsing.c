/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 14:29:40 by ndemont           #+#    #+#             */
/*   Updated: 2021/02/03 16:57:33 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		check_file(char *filename)
{
	int len;

	len = ft_strlen(filename);
	if (ft_strcmp(".rt", &filename[len - 3]))
		return (0);
	return (1);
}

int		get_type(char *line)
{
	int i;
	int len;
	static char	*list2[9] = {"R", "A", "c", "l", "sp", "sq", "cy", "tr", "pl"};

	i = 0;
	len = 1;
	while (i < 9)
	{
		if (i == 4)
			len = 2;
		if (ft_strnstr(list2[i], line, len))
			return (i);
		i++;
	}
	return (-1);
}

char		*fill_type2(int x, t_scene *s, char **line)
{
	char	*(*type[13])(char **, t_scene *);
	char	*error;

	type[0] = &parsing_r;
	type[1] = &parsing_a;
	type[2] = &parsing_c;
	type[3] = &parsing_l;
	type[4] = &parsing_sp;
	type[5] = &parsing_sq;
	type[6] = &parsing_cy;
	type[7] = &parsing_tr;
	type[8] = &parsing_pl;
	error = (*type[x])(line, s);
	return (error);
}

char		*fill_scene(t_scene *s, char **list)
{
	int		type;
	int		i;
	char	**line;
	char 	*error;

	i = 0;
	while (*list)
	{
		type = get_type((ft_split(*list, ' '))[0]);
		if (type == -1)
			return ("Wrong object");
		line = ft_split(*list, ' ');
		if ((error = fill_type2(type, s, line)))
			return (leaks(line, error));
		leaks(line, error);
		list++;
	}
	return (error);
}

int 	init_scene(t_scene *s, char **list)
{
	int c;
	int l;
	int o;

	c = 0;
	l = 0;
	o = 0;
	while (*list)
	{
		if ((*list)[0] == 'c' && (*list)[1] == ' ')
			c++;
		if ((*list)[0] == 'l')
			l++;
		if (((*list)[0] == 'p') || ((*list)[0] == 's') || \
			((*list)[0] == 'c' && (*list)[1] == 'y') || ((*list)[0] == 't'))
			o++;
		list++;
	}
	if (!(s->lights = malloc(sizeof(t_light) * (l + 1))))
		return (0);
	s->lights[0].i = -1;
	if (!(s->cameras = malloc(sizeof(t_camera) * (c + 1))))
		return (0);
	s->cam_nbr = c;
	s->cameras[0].f = -1;
	if (!(s->objects = malloc(sizeof(t_object) * (o + 1))))
		return (0);
	s->objects[0].type = -1;
	s->A.i = 0;
	return (1);
}

char		*check_parsing(char *file, t_scene *s)
{
	int		fd;
	char	*line;
	char	*content;
	char 	**list;
	int		ret;
	char 	*error;

	fd = open(file, O_RDONLY);
	error = NULL;
	if (fd < 0)
		return ("Opening file error\n.");
	ret = 1;
	content = 0;
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		if (ret < 0)
			return ("Reading file error.\n");
		content = ft_strjoin(content, line);
		content = ft_strjoin(content, "\n");
	}
	if (content[0] == '\n')
		return ("Empty file.");
	list = ft_split(content, '\n');
	close(fd);
	if (!init_scene(s, list))
		return (0);
	error = fill_scene(s, list);
	return (error);
}

