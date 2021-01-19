/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 14:29:40 by ndemont           #+#    #+#             */
/*   Updated: 2021/01/19 12:53:14 by ndemont          ###   ########.fr       */
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
	static char	*list = "RAclspsqcytrpl";
	char		*type;

	type = ft_strnstr(list, line, 14);
	if (!type)
		return (-1);
	return (type - list);
}

int		fill_type2(int x, t_scene *s, char **line)
{
	void (*type[13])(char **, t_scene *);

	type[0] = &parsing_r2;
	type[1] = &parsing_a2;
	type[2] = &parsing_c2;
	type[3] = &parsing_l2;
	type[4] = &parsing_sp2;
	type[6] = &parsing_sq2;
	type[8] = &parsing_cy2;
	type[10] = &parsing_tr2;
	type[12] = &parsing_pl2;
	(*type[x])(line, s);
	return (1);
}

int		fill_scene(t_scene *s, char **list)
{
	int		type;
	char	**line;

	while (*list)
	{
		type = get_type((ft_split(*list, ' '))[0]);
		line = ft_split(*list, ' ');
		fill_type2(type, s, line);
		list++;
	}
	return (1);
}

int		init_scene(t_scene *s, char **list)
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
	s->lights[0].i = 0;
	if (!(s->cameras = malloc(sizeof(t_camera) * (c + 1))))
		return (0);
	if (!(s->objects = malloc(sizeof(t_object) * (o + 1))))
		return (0);
	s->objects[0].type = -1;
	printf("l = %d\no = %d\nc = %d\n", l, o, c);
	return (1);
}

int		check_parsing(char *file, t_scene *s)
{
	int		fd;
	char	*line;
	char	*content;
	char 	**list;
	int		ret; 

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (2);
	ret = 1;
	content = 0;
	while (ret > 0)
	{
		if (ret < 0)
			return (3);
		ret = get_next_line(fd, &line);
		content = ft_strjoin(content, line);
		content = ft_strjoin(content, "\n");
	}
	list = ft_split(content, '\n');
	printf("content = [%s]\n", content);
	close(fd);
	if (!init_scene(s, list))
		return (0);
	fill_scene(s, list);
	printf("s->objects[0] = %f/%f/%f\n", s->objects[0].c.coord[0], s->objects[0].c.coord[1], s->objects[0].c.coord[2]);
	printf("s->objects[1] = %f/%f/%f\n", s->objects[1].c.coord[0], s->objects[1].c.coord[1], s->objects[1].c.coord[2]);
	printf("s->objects[2] = %f/%f/%f\n", s->objects[2].c.coord[0], s->objects[2].c.coord[1], s->objects[2].c.coord[2]);
	printf("s->objects[3] = %f/%f/%f\n", s->objects[3].c.coord[0], s->objects[3].c.coord[1], s->objects[3].c.coord[2]);
	printf("s->objects[4] = %f/%f/%f\n", s->objects[4].c.coord[0], s->objects[4].c.coord[1], s->objects[4].c.coord[2]);
	printf("s->objects[5] = %f/%f/%f\n", s->objects[5].c.coord[0], s->objects[5].c.coord[1], s->objects[5].c.coord[2]);
	printf("s->objects[6] = %f/%f/%f\n", s->objects[6].c.coord[0], s->objects[6].c.coord[1], s->objects[6].c.coord[2]);
	printf("s->objects[7] = %f/%f/%f\n", s->objects[7].c.coord[0], s->objects[7].c.coord[1], s->objects[7].c.coord[2]);
	printf("s->objects[8] = %f/%f/%f\n", s->objects[8].c.coord[0], s->objects[8].c.coord[1], s->objects[8].c.coord[2]);
	return (0);
}
