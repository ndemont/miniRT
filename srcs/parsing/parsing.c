/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 14:29:40 by ndemont           #+#    #+#             */
/*   Updated: 2021/02/08 13:40:49 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"

int			get_type(char *line)
{
	int			i;
	int			len;
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

char		*fill_type(int x, t_scene *s, char **line)
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
	char	**line;
	char	*error;

	while (*list)
	{
		type = get_type((ft_split(*list, ' '))[0]);
		if (type == -1)
			return ("Wrong object");
		line = ft_split(*list, ' ');
		if ((error = fill_type(type, s, line)))
			return (leaks(line, error));
		leaks(line, error);
		list++;
	}
	return (error);
}

void		ft_count_elem(char **list, int *c, int *l, int *o)
{
	*c = 0;
	*l = 0;
	*o = 0;
	while (*list)
	{
		if ((*list)[0] == 'c' && (*list)[1] == ' ')
			*c = *c + 1;
		if ((*list)[0] == 'l')
			*l = *l + 1;
		if (((*list)[0] == 'p') || ((*list)[0] == 's') || \
			((*list)[0] == 'c' && (*list)[1] == 'y') || ((*list)[0] == 't'))
			*o = *o + 1;
		list++;
	}
}

char		*check_parsing(char *file, t_scene *s)
{
	int		fd;
	char	*line;
	char	*content;
	char	**list;
	int		ret;

	if ((fd = open(file, O_RDONLY)) < 0)
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
	return (fill_scene(s, list));
}
