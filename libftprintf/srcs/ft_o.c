/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_o.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 15:00:48 by rkulahin          #+#    #+#             */
/*   Updated: 2018/12/28 10:39:05 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void			ft_precision_o(char **s, int *l, t_args *arg)
{
	char *s1;

	if (arg->precision > *l + arg->flag_hash)
	{
		*l = ft_instart_x(s, '0', arg->precision - *l - arg->flag_hash);
		if (**s == '-')
			*l = ft_instart_x(s, '0', 1);
	}
	else if (arg->precision == 0 && **s == '0')
	{
		s1 = *s;
		*s = NULL;
		free(s1);
		*l = 0;
	}
}

void			ft_o_mod(t_args *arg, va_list ap, int *index)
{
	index[0] += 1;
	if (arg->modifiers == 1)
		ft_ho_print(arg, ap);
	else if (arg->modifiers == 2)
		ft_hho_print(arg, ap);
	else if (arg->modifiers == 3)
		ft_lo_print(arg, ap);
	else if (arg->modifiers == 4)
		ft_llo_print(arg, ap);
	else
		ft_o_print(arg, ap);
}

void			ft_o_print(t_args *arg, va_list ap)
{
	int					l;
	char				*s;

	s = ft_itoa_base_x(va_arg(ap, unsigned int), 8);
	l = ft_strlen(s);
	ft_precision_o(&s, &l, arg);
	if (arg->width > (l + arg->flag_hash))
	{
		if (arg->flag_minus)
			l = ft_inend_x(&s, ' ', arg->width - l - arg->flag_hash);
		else if (arg->precision == -1 && arg->flag_zero)
			l = ft_instart_x(&s, '0', arg->width - l - arg->flag_hash);
	}
	if (s && arg->flag_hash && ft_atoi(s))
		l = ft_instart_x(&s, '0', 1);
	if (s == NULL && arg->flag_hash)
	{
		s = ft_strcpy(ft_strnew(1), "0");
		l++;
	}
	if (arg->width > l)
		l = ft_instart_x(&s, ' ', arg->width - l);
	ft_s_put(s);
}
