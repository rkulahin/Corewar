/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xx.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 11:19:41 by rkulahin          #+#    #+#             */
/*   Updated: 2018/12/28 16:16:56 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void			ft_xx_mod(t_args *arg, va_list ap, int *index)
{
	index[0] += 1;
	if (arg->modifiers == 1)
		ft_hxx_print(arg, ap);
	else if (arg->modifiers == 2)
		ft_hhxx_print(arg, ap);
	else if (arg->modifiers == 3)
		ft_lxx_print(arg, ap);
	else if (arg->modifiers == 4)
		ft_llxx_print(arg, ap);
	else
		ft_xx_print(arg, ap);
}

void			ft_xx_print(t_args *arg, va_list ap)
{
	int					l;
	char				*s;

	s = ft_itoa_base_xx(va_arg(ap, unsigned int), 16);
	l = ft_strlen(s);
	ft_precision_x(&s, &l, arg);
	if (arg->width > (l + (arg->flag_hash * 2)))
	{
		if (arg->flag_minus)
			l = ft_inend_x(&s, ' ', arg->width - l - (arg->flag_hash * 2));
		else if (arg->precision == -1 && arg->flag_zero)
			l = ft_instart_x(&s, '0', arg->width - l - (arg->flag_hash * 2));
	}
	if ((s && arg->flag_hash && ft_atoi(s)) ||
		(s && ft_strlen(s) != 1 && arg->flag_hash && ft_atoi(s) == 0))
	{
		l = ft_instart_x(&s, 'X', 1);
		l = ft_instart_x(&s, '0', 1);
	}
	if (arg->width > l)
		l = ft_instart_x(&s, ' ', arg->width - l);
	ft_s_put(s);
}
