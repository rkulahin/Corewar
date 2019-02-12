/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 08:29:17 by rkulahin          #+#    #+#             */
/*   Updated: 2018/10/30 18:27:00 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*node;
	t_list	*tmp;

	if (!(node = malloc(sizeof(t_list))) || !lst || !f)
		return (NULL);
	node = f(lst);
	tmp = node;
	while (lst->next)
	{
		node->next = malloc(sizeof(t_list));
		node->next = f(lst->next);
		lst = lst->next;
		node = node->next;
	}
	return (tmp);
}
