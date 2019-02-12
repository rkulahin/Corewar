/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 09:01:36 by rkulahin          #+#    #+#             */
/*   Updated: 2018/10/29 13:33:01 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ifneg(int *n, int *m, int *l)
{
	if (*n < 0)
	{
		*m = -1;
		(*l)++;
	}
}

char		*ft_itoa(int n)
{
	char	*str;
	int		m;
	int		l;

	m = 1;
	l = ft_cnumbers(n);
	if (n == 0)
	{
		str = ft_strnew(1);
		str[0] = '0';
		return (str);
	}
	ifneg(&n, &m, &l);
	if ((str = ft_strnew(l)))
	{
		if (m == -1)
			str[0] = '-';
		while (n != 0)
		{
			*(str + --l) = (n % 10) * m + '0';
			n = n / 10;
		}
	}
	return (str);
}
