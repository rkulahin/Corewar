/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 11:15:13 by rkulahin          #+#    #+#             */
/*   Updated: 2018/10/25 12:17:45 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *s, int c, size_t n)
{
	char		*s1;
	char		*s2;
	size_t		i;

	s1 = dest;
	s2 = (char *)s;
	i = -1;
	while (++i < n)
	{
		*(s1 + i) = *((unsigned char *)s2 + i);
		if (*((unsigned char *)s2 + i) == (unsigned char)c)
		{
			return (dest + i + 1);
		}
	}
	return (NULL);
}
