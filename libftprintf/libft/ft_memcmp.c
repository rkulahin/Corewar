/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 14:30:41 by rkulahin          #+#    #+#             */
/*   Updated: 2018/10/24 14:30:42 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *arr1, const void *arr2, size_t n)
{
	unsigned char	*a1;
	unsigned char	*a2;
	size_t			i;

	i = 0;
	a1 = (unsigned char *)arr1;
	a2 = (unsigned char *)arr2;
	while (i < n)
	{
		if (*(a1 + i) != *(a2 + i))
			return (*(a1 + i) - *(a2 + i));
		i++;
	}
	return (0);
}
