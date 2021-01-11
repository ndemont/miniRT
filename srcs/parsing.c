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
	int i;

	i = 0;
	while (list[i])
	{
		if (ft_strcmp())
	}
	return (1);
}

t_elem			create_line(char *line)
{
	int		i;
	t_elem	elem;
	char	**split;

	i = 0;
	split = ft_split(line, ' ');
	elem.type = split[0];
	if (ft_strcmp("R", elem.type))
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
		printf("type %d = %s\n", i, scene[i].type);
		i++;
	}
	close(fd);
	return (0);
}