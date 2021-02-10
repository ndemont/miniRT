/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 11:37:37 by ndemont           #+#    #+#             */
/*   Updated: 2021/02/10 13:24:36 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"

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
		return (print_errors("Wrong number of arguments."));
	if (!check_file(av[1]))
		return (print_errors("Wrong type of file."));
	if ((error = check_parsing(av[1], s)))
	{
		free_scene(0, s);
		return (print_errors(error));
	}
	if (ac == 3)
	{
		if (ft_strcmp(av[2], "-save"))
			return (print_errors("Wrong option\n"));
		init_general(s);
		save_bmp(s);
		exit(free_scene(0, s));
	}
	return (0);
}
