/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strstr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 11:50:23 by rkulahin          #+#    #+#             */
/*   Updated: 2018/10/26 14:56:09 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *strb, const char *stra)
{
	int	i;
	int	find_i;
	int	rem;

	i = 0;
	if (*(stra + i) == '\0')
		return ((char*)(strb));
	while (*(strb + i))
	{
		find_i = 0;
		if (*(strb + i) == *(stra + find_i))
		{
			rem = i;
			while (*(strb + i) == *(stra + find_i))
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
