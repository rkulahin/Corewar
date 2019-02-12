/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 16:43:44 by rkulahin          #+#    #+#             */
/*   Updated: 2018/10/25 17:02:40 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *app, size_t n)
{
	int				i;
	unsigned long	j;

	i = 0;
	j = 0;
	while (*(dest + i))
		i++;
	while (*(app + j) && j < (unsigned long)n)
	{
		*(dest + i) = *(app + j);
		j++;
		i++;
	}
	*(dest + i) = '\0';
	return (dest);
}
