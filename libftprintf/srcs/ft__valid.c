/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft__valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 13:26:34 by rkulahin          #+#    #+#             */
/*   Updated: 2018/12/28 10:31:19 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft__print(t_args *arg, int *index, const char *str)
{
	char	*ptr;
	int		i;
	int		len;
	int		c;

	i = 0;
	c = str[index[0]];
	index[0] += 1;
	if (arg->width > 1)
	{
		len = arg->width;
		if ((!arg->flag_zero) || (arg->flag_zero && arg->flag_minus))
			ptr = ft_memset(ft_strnew(len), ' ', len);
		else
			ptr = ft_memset(ft_strnew(len), '0', len);
		if (arg->flag_minus == 1)
			ptr[0] = c;
		else
			ptr[len - 1] = c;
		ft_s_put(ptr);
		return ;
	}
	ft_putchar(c);
	g_ret += 1;
}
