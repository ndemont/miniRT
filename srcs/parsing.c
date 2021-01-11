#include "minirt.h"

int			check_file(char *filename)
{
	int len;

	len = ft_strlen(filename);
	if (ft_strcmp(".rt", &filename[len - 3]))
		return (0);
	return (1);
}


int			check_line(char *line)
{
	(void)line;
	return (1);
}

int		get_type(char *line)
{
	char *list = "RAclspsqcytrpl";
	char *type;

	type = ft_strnstr(list, line, 14);
	if (!type)
		return (-1);
	return (type - list);
}

int		fill_type(int x, t_elem *elem, char **split)
{
	void (*type[13])(char **, t_elem *);

	type[0] = &parsing_R;
	type[1] = &parsing_A;
	type[2] = &parsing_c;
	type[3] = &parsing_l;
	type[4] = &parsing_sp;
	type[6] = &parsing_sq;
	type[8] = &parsing_cy;
	type[10] = &parsing_tr;
	type[12] = &parsing_pl;
	(*type[x])(split, elem);
	return (1);
}

void	init_elem(t_elem *elem)
{
	elem->type = "\0";
	elem->size[0] = 0;
	elem->size[1] = 0;
	elem->v.coord[0] = 0;
	elem->v.coord[1] = 0;
	elem->v.coord[2] = 0;
	elem->origin.coord[0] = 0;
	elem->origin.coord[1] = 0;
	elem->origin.coord[2] = 0;
	elem->focal = 0;
	elem->color.coord[0] = 0;
	elem->color.coord[1] = 0;
	elem->color.coord[2] = 0;
	elem->ratio = 0;
	elem->ray = 0;
}

t_elem			create_line(char *line)
{
	int		i;
	int		type;
	t_elem	elem;
	char	**split;

	i = 0;
	split = ft_split(line, ' ');
	init_elem(&elem);
	elem.type = split[0];
	type = get_type(elem.type);
	fill_type(type, &elem, split);
	printf("TYPE %s :\nR = %f/%f\nA = %f,%f/%f/%f\n", elem.type, elem.size[0], elem.size[1], elem.ratio, elem.color.coord[0], elem.color.coord[1], elem.color.coord[2]);
	return(elem);
}

int		check_parsing(char *file)
{
	int		i;
	int		fd;
	char	*line;
	int		ret;
	int		count;
	t_elem	*scene;

	i = 0;
	fd = open(file, O_RDONLY);
	count = 0;
	if (fd < 0)
		return (2);
	ret = 1;
	// faire le comptage en meme temps que la verification
	while (ret > 0)
	{
		if (ret < 0)
			return (3);
		ret = get_next_line(fd, &line);
		count++;
		printf("%s\n", line);
	}
	close(fd);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (2);
	printf("count = %d\n", count);
	scene = malloc(sizeof(t_elem) * count);
	while (i < count)
	{
		get_next_line(fd, &line);
		//check_line(line);
		scene[i] = create_line(line);
		//printf("type %d = %s\n", i, scene[i].type);
		i++;
	}
	close(fd);
	return (0);
}