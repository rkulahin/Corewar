/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 14:30:41 by rkulahin          #+#    #+#             */
/*   Updated: 2018/10/26 17:17:32 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *str1, const char *str2, size_t n)
{
	unsigned char	*a1;
	unsigned char	*a2;
	size_t			i;

	i = 0;
	if (n == 0)
		return (0);
	a1 = (unsigned char *)str1;
	a2 = (unsigned char *)str2;
	if (*(a1 + i) == '\0' || *(a2 + i) == '\0')
		return (*(a1 + i) - *(a2 + i));
	while ((*(a1 + i) != '\0' || *(a2 + i) != '\0') && i < n)
	{
		if (*(a1 + i) != *(a2 + i))
			return (*(a1 + i) - *(a2 + i));
		i++;
	}
	return (0);
}
