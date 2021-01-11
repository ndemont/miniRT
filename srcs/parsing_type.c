#include "minirt.h"

void		parsing_R(char **line, t_elem *elem)
{
	elem->size[0] = ft_atof(line[1]);
	elem->size[1] = ft_atof(line[2]);
}

void		parsing_A(char **line, t_elem *elem)
{
	char **split;

	printf("line 0 = %s\nline 1 = %s\n", line[0], line[1]);
	elem->ratio = ft_atof(line[1]);
	printf("atof = %f\n", ft_atof(line[1]));
	split = ft_split(line[2], ',');

	elem->color.coord[0] = ft_atof(split[0]);
	elem->color.coord[1] = ft_atof(split[1]);
	elem->color.coord[2] = ft_atof(split[2]);
}

void		parsing_c(char **line, t_elem *elem)
{
	(void)line;
	(void)elem;
}

void		parsing_l(char **line, t_elem *elem)
{
	(void)line;
	(void)elem;
}

void		parsing_pl(char **line, t_elem *elem)
{
	(void)line;
	(void)elem;
}

void		parsing_sp(char **line, t_elem *elem)
{
	(void)line;
	(void)elem;
}

void		parsing_sq(char **line, t_elem *elem)
{
	(void)line;
	(void)elem;
}

void		parsing_cy(char **line, t_elem *elem)
{
	(void)line;
	(void)elem;
}

void		parsing_tr(char **line, t_elem *elem)
{
	(void)line;
	(void)elem;
}