/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 10:50:06 by rkulahin          #+#    #+#             */
/*   Updated: 2018/10/25 11:29:25 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *s, size_t n)
{
	char		*s1;
	const char	*s2;
	size_t		i;

	s1 = dest;
	s2 = s;
	i = -1;
	while (++i < n)
		*(s1 + i) = *(s2 + i);
	return (dest);
}
