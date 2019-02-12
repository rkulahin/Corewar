/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 12:28:26 by rkulahin          #+#    #+#             */
/*   Updated: 2018/10/29 13:23:38 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	st;
	size_t	e;
	char	*ptr;

	st = 0;
	if (s)
	{
		e = ft_strlen(s) - 1;
		while (s[st] == ' ' || s[st] == '\t' || s[st] == '\n')
			st++;
		if (s[st] == '\0')
		{
			ptr = ft_strnew(1);
			return ((char *)ptr);
		}
		while (s[e] == ' ' || s[e] == '\t' || s[e] == '\n')
			e--;
		ptr = ft_strnew(e - st);
		if (ptr)
			ptr = ft_strsub(s, st, e - st + 1);
		return (ptr);
	}
	return (NULL);
}
