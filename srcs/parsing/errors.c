/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 11:37:37 by ndemont           #+#    #+#             */
/*   Updated: 2021/02/15 22:36:55 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"

char	*fill_scene(t_scene *s, char **list)
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

int		check_file(char *filename)
{
	int len;

	len = ft_strlen(filename);
	if (ft_strcmp(".rt", &filename[len - 3]))
		return (0);
	return (1);
}

int		print_errors(char *error)
{
	ft_printf("%s\n", error);
	return (1);
}

int		check_errors(int ac, char **av, t_scene *s)
{
	char	*error;

	if (ac < 2 || ac > 3)
		return (print_errors("Error 1: Wrong number of arguments."));
	if (!check_file(av[1]))
		return (print_errors("Error 2: Wrong type of file."));
	if ((error = check_parsing(av[1], s)))
	{
		free_scene(0, s);
		return (print_errors(error));
	}
	if (ac == 3)
	{
		if (ft_strcmp(av[2], "-save"))
			return (print_errors("Error 10: Unknown option."));
		if ((error = save_bmp(s)))
			return (print_errors(error));
		exit(free_scene(0, s));
	}
	return (0);
}
