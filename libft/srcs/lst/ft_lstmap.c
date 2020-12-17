/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 18:58:28 by ndemont           #+#    #+#             */
/*   Updated: 2020/11/16 11:52:08 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ft_lstdup(t_list *lst, void (*del)(void *))
{
	t_list	*elem;
	t_list	*begin;

	if (!lst)
		return (0);
	begin = ft_lstnew(lst->content);
	if (!begin)
		return (0);
	lst = lst->next;
	while (lst)
	{
		elem = ft_lstnew(lst->content);
		if (!elem)
		{
			ft_lstclear(&elem, del);
			return (0);
		}
		ft_lstadd_back(&begin, elem);
		lst = lst->next;
	}
	return (begin);
}

t_list			*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*map;
	t_list	*begin;

	if (!lst)
		return (0);
	map = ft_lstdup(lst, del);
	if (!map)
		return (0);
	begin = map;
	while (map)
	{
		map->content = (f)(map->content);
		map = map->next;
	}
	return (begin);
}
