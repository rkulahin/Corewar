/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_u.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 12:13:09 by rkulahin          #+#    #+#             */
/*   Updated: 2018/12/27 12:26:49 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void			ft_u_mod(t_args *arg, va_list ap, int *index)
{
	index[0] += 1;
	if (arg->modifiers == 1)
		ft_hu_print(arg, ap);
	else if (arg->modifiers == 2)
		ft_hhu_print(arg, ap);
	else if (arg->modifiers == 3)
		ft_lu_print(arg, ap);
	else if (arg->modifiers == 4)
		ft_llu_print(arg, ap);
	else
		ft_u_print(arg, ap);
}

void			ft_u_print(t_args *arg, va_list ap)
{
	int					l;
	char				*s;

	s = ft_itoa_base_x_u(va_arg(ap, unsigned int), 10);
	l = ft_strlen(s);
	ft_precision_x(&s, &l, arg);
	if (arg->width > (l))
	{
		if (arg->flag_minus)
			l = ft_inend_x(&s, ' ', arg->width - l);
		else if (arg->precision == -1 && arg->flag_zero)
			l = ft_instart_x(&s, '0', arg->width - l);
	}
	if (arg->width > l)
		l = ft_instart_x(&s, ' ', arg->width - l);
	ft_s_put(s);
}
