/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 12:02:32 by rkulahin          #+#    #+#             */
/*   Updated: 2018/10/26 18:40:04 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *s, size_t n)
{
	char		*s1;
	char		*s2;
	size_t		i;

	i = -1;
	s1 = (char *)dest;
	s2 = (char *)s;
	if (s2 < s1)
		while ((int)--n >= 0)
			*(s1 + n) = *(s2 + n);
	else
		while (++i < n)
			*(s1 + i) = *(s2 + i);
	return (dest);
}
