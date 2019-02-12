/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 08:36:32 by rkulahin          #+#    #+#             */
/*   Updated: 2018/10/25 14:07:44 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	int		l;
	int		i;
	char	*r;

	l = 0;
	while (str[l])
		l++;
	r = malloc(l + 1);
	if (r == NULL)
		return (NULL);
	i = 0;
	while (i < l)
	{
		r[i] = str[i];
		i++;
	}
	r[i] = '\0';
	return (r);
}
