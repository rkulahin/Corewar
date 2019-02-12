/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 13:43:57 by rkulahin          #+#    #+#             */
/*   Updated: 2018/12/26 14:09:42 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void			ft_p_print(t_args *arg, va_list ap, int *len)
{
	int					l;
	char				*s;

	len[0] += 1;
	s = ft_itoa_base_x_u(va_arg(ap, unsigned long long), 16);
	l = ft_strlen(s);
	ft_precision_x(&s, &l, arg);
	if (arg->width > (l + 2))
	{
		if (arg->flag_minus)
			l = ft_inend_x(&s, ' ', arg->width - l - 2);
		else if (arg->precision == -1 && arg->flag_zero)
			l = ft_instart_x(&s, '0', arg->width - l - 2);
	}
	l = ft_instart_x(&s, 'x', 1);
	l = ft_instart_x(&s, '0', 1);
	if (arg->width > l)
		l = ft_instart_x(&s, ' ', arg->width - l);
	ft_s_put(s);
}
