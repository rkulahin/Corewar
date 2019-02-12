/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 17:37:18 by rkulahin          #+#    #+#             */
/*   Updated: 2018/10/29 18:15:35 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*list;

	if ((list = malloc(sizeof(t_list))))
	{
		list->next = NULL;
		if (content == NULL)
		{
			list->content = NULL;
			list->content_size = 0;
		}
		else
		{
			list->content = malloc(content_size);
			list->content_size = content_size;
			list->content = ft_strncpy(list->content, content, content_size);
		}
		return (list);
	}
	return (NULL);
}
