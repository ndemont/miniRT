#include "minirt.h"

void		parsing_R(char **line, t_elem *elem)
{
	elem->size[0] = ft_atof(line[1]);
	elem->size[1] = ft_atof(line[2]);
}

void		parsing_A(char **line, t_elem *elem)
{
	char **split;

	elem->ratio = ft_atof(line[1]);
	split = ft_split(line[2], ',');
	elem->color.coord[0] = ft_atof(split[0]);
	elem->color.coord[1] = ft_atof(split[1]);
	elem->color.coord[2] = ft_atof(split[2]);
}

void		parsing_c(char **line, t_elem *elem)
{
	char **split;

	split = ft_split(line[1], ',');
	elem->origin.coord[0] = ft_atof(split[0]);
	elem->origin.coord[1] = ft_atof(split[1]);
	elem->origin.coord[2] = ft_atof(split[2]);
	split = ft_split(line[2], ',');
	elem->v.coord[0] = ft_atof(split[0]);
	elem->v.coord[1] = ft_atof(split[1]);
	elem->v.coord[2] = ft_atof(split[2]);
	elem->focal = ft_atof(line[3]);
}

void		parsing_l(char **line, t_elem *elem)
{
	char **split;

	split = ft_split(line[1], ',');
	elem->origin.coord[0] = ft_atof(split[0]);
	elem->origin.coord[1] = ft_atof(split[1]);
	elem->origin.coord[2] = ft_atof(split[2]);
	elem->ratio = ft_atof(line[2]);
	split = ft_split(line[3], ',');
	elem->color.coord[0] = ft_atof(split[0]);
	elem->color.coord[1] = ft_atof(split[1]);
	elem->color.coord[2] = ft_atof(split[2]);
}

void		parsing_pl(char **line, t_elem *elem)
{
	char **split;

	split = ft_split(line[1], ',');
	elem->origin.coord[0] = ft_atof(split[0]);
	elem->origin.coord[1] = ft_atof(split[1]);
	elem->origin.coord[2] = ft_atof(split[2]);
	split = ft_split(line[2], ',');
	elem->v.coord[0] = ft_atof(split[0]);
	elem->v.coord[1] = ft_atof(split[1]);
	elem->v.coord[2] = ft_atof(split[2]);
	split = ft_split(line[3], ',');
	elem->color.coord[0] = ft_atof(split[0]);
	elem->color.coord[1] = ft_atof(split[1]);
	elem->color.coord[2] = ft_atof(split[2]);
}

void		parsing_sp(char **line, t_elem *elem)
{
	char **split;

	split = ft_split(line[1], ',');
	elem->origin.coord[0] = ft_atof(split[0]);
	elem->origin.coord[1] = ft_atof(split[1]);
	elem->origin.coord[2] = ft_atof(split[2]);
	elem->ray = ft_atof(line[2]) / 2;
	split = ft_split(line[3], ',');
	elem->color.coord[0] = ft_atof(split[0]);
	elem->color.coord[1] = ft_atof(split[1]);
	elem->color.coord[2] = ft_atof(split[2]);
}

void		parsing_sq(char **line, t_elem *elem)
{
	char **split;

	split = ft_split(line[1], ',');
	elem->origin.coord[0] = ft_atof(split[0]);
	elem->origin.coord[1] = ft_atof(split[1]);
	elem->origin.coord[2] = ft_atof(split[2]);
	split = ft_split(line[2], ',');
	elem->v.coord[0] = ft_atof(split[0]);
	elem->v.coord[1] = ft_atof(split[1]);
	elem->v.coord[2] = ft_atof(split[2]);
	elem->height = ft_atof(line[3]);
	split = ft_split(line[4], ',');
	elem->color.coord[0] = ft_atof(split[0]);
	elem->color.coord[1] = ft_atof(split[1]);
	elem->color.coord[2] = ft_atof(split[2]);
}

void		parsing_cy(char **line, t_elem *elem)
{
	char **split;

	split = ft_split(line[1], ',');
	elem->origin.coord[0] = ft_atof(split[0]);
	elem->origin.coord[1] = ft_atof(split[1]);
	elem->origin.coord[2] = ft_atof(split[2]);
	split = ft_split(line[2], ',');
	elem->v.coord[0] = ft_atof(split[0]);
	elem->v.coord[1] = ft_atof(split[1]);
	elem->v.coord[2] = ft_atof(split[2]);
	elem->ray = ft_atof(line[3]);
	elem->height = ft_atof(line[4]);
	split = ft_split(line[5], ',');
	elem->color.coord[0] = ft_atof(split[0]);
	elem->color.coord[1] = ft_atof(split[1]);
	elem->color.coord[2] = ft_atof(split[2]);
}

void		parsing_tr(char **line, t_elem *elem)
{
	char **split;

	split = ft_split(line[1], ',');
	elem->origin.coord[0] = ft_atof(split[0]);
	elem->origin.coord[1] = ft_atof(split[1]);
	elem->origin.coord[2] = ft_atof(split[2]);
	split = ft_split(line[2], ',');
	elem->v.coord[0] = ft_atof(split[0]);
	elem->v.coord[1] = ft_atof(split[1]);
	elem->v.coord[2] = ft_atof(split[2]);
	split = ft_split(line[3], ',');
	elem->v2.coord[0] = ft_atof(split[0]);
	elem->v2.coord[1] = ft_atof(split[1]);
	elem->v2.coord[2] = ft_atof(split[2]);
	split = ft_split(line[4], ',');
	elem->color.coord[0] = ft_atof(split[0]);
	elem->color.coord[1] = ft_atof(split[1]);
	elem->color.coord[2] = ft_atof(split[2]);
}