/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strstr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 11:50:23 by rkulahin          #+#    #+#             */
/*   Updated: 2018/10/26 16:17:47 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *strb, const char *stra, size_t n)
{
	size_t	i;
	int		find_i;
	int		rem;

	i = 0;
	if (*(stra + i) == '\0')
		return ((char*)(strb));
	while (*(strb + i) && i < n)
	{
		find_i = 0;
		if (*(strb + i) == *(stra + find_i))
		{
			rem = i;
			while (*(strb + i) == *(stra + find_i) && i < n)
			{
				if (*(stra + find_i + 1) == '\0')
					return ((char*)(strb + rem));
				find_i++;
				i++;
			}
			i = rem;
		}
		i++;
	}
	return (NULL);
}
