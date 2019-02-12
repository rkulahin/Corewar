/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 11:59:15 by rkulahin          #+#    #+#             */
/*   Updated: 2018/10/28 13:20:56 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char *ptr;

	if (s1 && s2)
	{
		ptr = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
		if (ptr)
		{
			ptr = ft_strcpy(ptr, s1);
			ptr = ft_strcat(ptr, s2);
		}
		return (ptr);
	}
	return (NULL);
}
