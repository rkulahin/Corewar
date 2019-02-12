/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 14:50:18 by rkulahin          #+#    #+#             */
/*   Updated: 2018/10/25 15:40:11 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *s, size_t n)
{
	size_t i;

	i = -1;
	while (++i < n)
	{
		if (*(s + i))
			*(dest + i) = *(s + i);
		else
			while (i < n)
			{
				*(dest + i) = '\0';
				i++;
			}
	}
	return (dest);
}
