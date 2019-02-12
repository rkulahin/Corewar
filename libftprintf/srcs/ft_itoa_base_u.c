/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_u.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 16:54:31 by rkulahin          #+#    #+#             */
/*   Updated: 2018/12/20 19:32:26 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void			rec_xx_u(unsigned long long v, unsigned int b, char *r, int *i)
{
	char	base[17];

	ft_strcpy(base, "0123456789ABCDEF");
	if (b <= v)
		rec_xx_u(v / b, b, r, i);
	r[(*i)++] = base[ABS(v % b)];
}

void			rec_x_u(unsigned long long v, unsigned int b, char *r, int *i)
{
	char	base[17];

	ft_strcpy(base, "0123456789abcdef");
	if (b <= v)
		rec_x_u(v / b, b, r, i);
	r[(*i)++] = base[ABS(v % b)];
}

char			*ft_itoa_base_xx_u(unsigned long long value, unsigned int base)
{
	char	*ret;
	int		i;

	ret = (char *)malloc(sizeof(char) * 100);
	i = 0;
	rec_xx_u(value, base, ret, &i);
	ret[i] = '\0';
	return (ret);
}

char			*ft_itoa_base_x_u(unsigned long long value, unsigned int base)
{
	char	*ret;
	int		i;

	ret = (char *)malloc(sizeof(char) * 100);
	i = 0;
	rec_x_u(value, base, ret, &i);
	ret[i] = '\0';
	return (ret);
}
