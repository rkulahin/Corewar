/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_c.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 15:57:38 by rkulahin          #+#    #+#             */
/*   Updated: 2018/12/28 10:24:32 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void		custom_c(char c, char *str, int i)
{
	if (i == 1)
	{
		ft_putchar(c);
		ft_s_put(str);
	}
	else
	{
		ft_s_put(str);
		ft_putchar(c);
	}
}

void			ft_c_print(t_args *arg, va_list ap, int *index)
{
	int		c;
	char	*ptr;
	int		i;
	int		len;

	index[0] += 1;
	i = 0;
	len = 0;
	c = va_arg(ap, int);
	if (arg->width > 1)
	{
		len += arg->width - 1;
		if ((!arg->flag_zero) || (arg->flag_zero && arg->flag_minus))
			ptr = ft_memset(ft_strnew(len), ' ', len);
		else
			ptr = ft_memset(ft_strnew(len), '0', len);
		if (arg->flag_minus == 1)
			custom_c(c, ptr, 1);
		else
			custom_c(c, ptr, 0);
		g_ret++;
		return ;
	}
	ft_putchar(c);
	g_ret += 1;
}
