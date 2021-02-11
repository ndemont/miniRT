/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 14:29:40 by ndemont           #+#    #+#             */
/*   Updated: 2021/02/11 19:09:25 by ndemont          ###   ########.fr       */
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

	error = 0;
	while (*list)
	{
		line = ft_split(*list, ' ');
		type = get_type(line[0]);
		if (type == -1)
			return ("Error 7: Unknown object.");
		if ((error = fill_type(type, s, line)))
			return (free_split(line, error));
		free_split(line, error);
		list++;
	}
	if ((int)(s->r[0]) == 0 || (int)(s->r[1]) == 0)
		return ("Error 8: Resolution has to be set to open a window.");
	if (s->cam_nbr < 1)
		return ("Error 9: One camera has to be set to create a view.");
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

static char	*read_file(int fd)
{
	char	*content;
	char	*tmp;
	char	*line;
	int		ret;

	ret = 1;
	content = 0;
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		if (ret < 0)
			return (0);
		tmp = content;
		content = ft_strjoin(content, line);
		free(tmp);
		tmp = content;
		content = ft_strjoin(content, "\n");
		free(tmp);
		free(line);
	}
	return (content);
}

char		*check_parsing(char *file, t_scene *s)
{
	int		fd;
	char	*content;
	char	**list;
	int		ret;
	char	*ret2;

	if ((fd = open(file, O_RDONLY)) < 0)
		return ("Error 3: Cannot open file.");
	ret = 1;
	if (!(content = read_file(fd)))
		return ("Error 4: Cannot read file.");
	if (content[0] == '\n')
		return ("Error 5: Empty file.");
	list = ft_split(content, '\n');
	free_parsing(content);
	close(fd);
	if (!init_scene(s, list))
	{
		free_scene(list, s);
		return ("Error 6: memory allocation failure.");
	}
	ret2 = fill_scene(s, list);
	free_split(list, 0);
	return (ret2);
}
