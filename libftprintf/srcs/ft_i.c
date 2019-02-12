/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_i.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 14:11:01 by rkulahin          #+#    #+#             */
/*   Updated: 2018/12/28 10:35:04 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void			ft_i_mod(t_args *arg, va_list ap, int *index)
{
	index[0] += 1;
	if (arg->modifiers == 1)
		ft_hi_print(arg, ap);
	else if (arg->modifiers == 2)
		ft_hhi_print(arg, ap);
	else if (arg->modifiers == 3)
		ft_li_print(arg, ap);
	else if (arg->modifiers == 4)
		ft_lli_print(arg, ap);
	else
		ft_i_print(arg, ap);
}

void			ft_i_print(t_args *arg, va_list ap)
{
	int					l;
	char				*s;

	s = ft_itoa_base_x(va_arg(ap, int), 10);
	l = ft_strlen(s);
	ft_precision_x(&s, &l, arg);
	if (arg->width > (l))
	{
		if (arg->flag_minus)
			l = ft_inend_x(&s, ' ', arg->width - l - arg->flag_plus);
		else if (arg->precision == -1 && arg->flag_zero && s[0] != '-')
			l = ft_instart_x(&s, '0', arg->width - l -
				arg->flag_plus - arg->flag_space);
		else if (arg->precision == -1 && arg->flag_zero && s[0] == '-')
			l = ft_instart_x(&s, '0', arg->width - l);
	}
	if (arg->flag_plus && s[0] != '-')
		l = ft_instart_x(&s, '+', 1);
	if (s && !arg->flag_plus && s[0] != '-' && arg->flag_space)
		l = ft_instart_x(&s, ' ', 1);
	if (arg->width > l)
		l = ft_instart_x(&s, ' ', arg->width - l);
	ft_s_put(s);
}
