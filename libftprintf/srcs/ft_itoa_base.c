/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 09:30:49 by rkulahin          #+#    #+#             */
/*   Updated: 2018/12/26 14:45:03 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void			rec_xx(long long value, int b, char *ret, int *i)
{
	char	base[17];

	ft_strcpy(base, "0123456789ABCDEF");
	if (value <= -b || b <= value)
		rec_xx(value / b, b, ret, i);
	ret[(*i)++] = base[ABS(value % b)];
}

void			rec_x(long long value, int b, char *ret, int *i)
{
	char	base[17];

	ft_strcpy(base, "0123456789abcdef");
	if (value <= -b || b <= value)
		rec_x(value / b, b, ret, i);
	ret[(*i)++] = base[ABS(value % b)];
}

char			*ft_itoa_base_xx(long long value, int base)
{
	char	*ret;
	int		i;

	ret = (char *)malloc(sizeof(char) * 100);
	i = 0;
	if (base == 10 && value < 0)
		ret[i++] = '-';
	rec_xx(value, base, ret, &i);
	ret[i] = '\0';
	return (ret);
}

char			*ft_itoa_base_x(long long value, int base)
{
	char	*ret;
	int		i;

	ret = (char *)malloc(sizeof(char) * 100);
	i = 0;
	if (base == 10 && value < 0)
		ret[i++] = '-';
	rec_x(value, base, ret, &i);
	ret[i] = '\0';
	return (ret);
}
