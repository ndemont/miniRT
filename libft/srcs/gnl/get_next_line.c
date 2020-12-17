/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 20:29:12 by ndemont           #+#    #+#             */
/*   Updated: 2020/11/22 14:04:05 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_nl	*init_gnl(int fd)
{
	t_nl	*new;

	if (!(new = malloc(sizeof(t_nl))))
		return (NULL);
	new->fd = fd;
	new->buf = 0;
	new->prev = 0;
	new->next = 0;
	return (new);
}

t_nl	*get_gnl(t_nl *gnl, int fd)
{
	if (!gnl)
	{
		if (!(gnl = init_gnl(fd)))
			return (NULL);
		return (gnl);
	}
	while (gnl->prev)
		gnl = gnl->prev;
	while (gnl->next && gnl->fd != fd)
		gnl = gnl->next;
	if (gnl->fd != fd)
	{
		gnl->next = init_gnl(fd);
		gnl->next->prev = gnl;
		return (gnl->next);
	}
	else
		return (gnl);
}

int		read_gnl(t_nl *gnl)
{
	char	*buf;
	char	*tmp;
	int		ret;

	if (!(buf = (char*)malloc((BUFFER_SIZE + 1) * sizeof(char))))
		return (-1);
	while (!gnl->buf || !ft_strchr(gnl->buf, '\n'))
	{
		ret = read(gnl->fd, buf, BUFFER_SIZE);
		if (ret > 0)
			buf[ret] = '\0';
		else
			break ;
		tmp = gnl->buf;
		gnl->buf = ft_strjoin(gnl->buf, buf);
		free(tmp);
	}
	free(buf);
	return (ret);
}

int		check_gnl(t_nl *gnl, char **line)
{
	char	*tmp;
	int		len;

	if (gnl->buf && ft_strchr(gnl->buf, '\n'))
	{
		len = ft_strchr(gnl->buf, '\n') - gnl->buf;
		if (!(*line = ft_substr(gnl->buf, 0, len)))
			return (-1);
		tmp = gnl->buf;
		gnl->buf = ft_substr(gnl->buf, len + 1, ft_strlen(gnl->buf));
		free(tmp);
		return (1);
	}
	if (gnl->buf)
	{
		*line = ft_strdup(gnl->buf);
		free(gnl->buf);
	}
	else
		*line = ft_strdup("\0");
	if (gnl->prev)
		gnl->prev->next = gnl->next;
	if (gnl->next)
		gnl->next->prev = gnl->prev;
	return (0);
}

int		get_next_line(int fd, char **line)
{
	static t_nl	*gnl;
	int			check;
	t_nl		*tmp;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (!(gnl = get_gnl(gnl, fd)))
		return (-1);
	if ((read_gnl(gnl)) < 0)
		return (-1);
	if (!(check = check_gnl(gnl, line)))
	{
		tmp = gnl;
		if (gnl->prev)
			gnl = gnl->prev;
		else if (gnl->next)
			gnl = gnl->next;
		free(tmp);
		if (gnl == tmp)
			gnl = NULL;
	}
	return (check);
}
