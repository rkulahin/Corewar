/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 15:41:06 by rkulahin          #+#    #+#             */
/*   Updated: 2018/10/25 16:25:05 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, const char *app)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (*(dest + i))
		i++;
	while (*(app + j))
	{
		*(dest + i) = *(app + j);
		j++;
		i++;
	}
	*(dest + i) = '\0';
	return (dest);
}
