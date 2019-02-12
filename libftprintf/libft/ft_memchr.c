/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 13:43:27 by rkulahin          #+#    #+#             */
/*   Updated: 2018/10/25 13:47:01 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *arr, int c, size_t n)
{
	const char	*s;
	size_t		i;

	s = (const char *)arr;
	i = -1;
	while (++i < n)
	{
		if (*(s + i) == (char)c)
			return ((void *)s + i);
	}
	return (NULL);
}
