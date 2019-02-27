/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 14:46:32 by rkulahin          #+#    #+#             */
/*   Updated: 2019/02/27 15:10:00 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			vm_atoi_16(char *str)
{
	int		i;
	int		m;

	m = 0;
	i = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	while ((*str >= '0' && *str <= '9') || (*str >= 'a' && *str <= 'f'))
	{
		if (*str >= '0' && *str <= '9')
			i = i * 16 + *str - '0';
		else
			i = i * 16 + *str - 'a' + 10;
		str++;
	}
	if (m == 1)
		i = -i;
	return (i);
}

char		*vm_itoa_16(long long numb)
{
	char		*str;
	int			i;
	long long	v1;

	i = 8;
	str = ft_memset(ft_strnew(i), '0', 8);
	while (i-- != 0)
	{
		if (ABS(numb % 16) > 9)
			v1 = ABS(numb % 16) - 10 + 'a';
		else
			v1 = ABS(numb % 16) + '0';
		str[i] = v1;
		numb /= 16;
	}
	return (str);
}

int			*check_arg(int nb)
{
	int		*arr;
	int		i;

	i = 0;
	arr = (int *)malloc(sizeof(int) * 3);
	ft_bzero(arr, sizeof(int) * 3);
	while (i < 3)
	{
		if ((nb & 192) == 192)
			arr[i] = T_IND;
		else if ((nb & 192) == 128)
			arr[i] = T_DIR;
		else if ((nb & 192) == 64)
			arr[i] = T_REG;
		nb = nb << 2;
		i++;
	}
	return (arr);
}
