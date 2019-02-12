/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 16:22:41 by rkulahin          #+#    #+#             */
/*   Updated: 2018/10/26 16:43:08 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *str1, const char *str2)
{
	unsigned char	*a1;
	unsigned char	*a2;
	size_t			i;

	i = 0;
	a1 = (unsigned char *)str1;
	a2 = (unsigned char *)str2;
	while (*(a1 + i) && *(a2 + i))
	{
		if (*(a1 + i) != *(a2 + i))
			return (*(a1 + i) - *(a2 + i));
		i++;
	}
	if (*(a1 + i) == '\0' || *(a2 + i) == '\0')
		return (*(a1 + i) - *(a2 + i));
	return (0);
}
