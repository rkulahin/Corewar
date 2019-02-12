/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_i_mod.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 14:18:53 by rkulahin          #+#    #+#             */
/*   Updated: 2018/12/26 18:23:40 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void			ft_hi_print(t_args *arg, va_list ap)
{
	int					l;
	char				*s;

	s = ft_itoa_base_x((short)va_arg(ap, int), 10);
	l = ft_strlen(s);
	ft_precision_x(&s, &l, arg);
	if (arg->width > (l))
	{
		if (arg->flag_minus)
			l = ft_inend_x(&s, ' ', arg->width - l - arg->flag_plus);
		else if (arg->precision == -1 && arg->flag_zero && s[0] != '-')
			l = ft_instart_x(&s, '0', arg->width - l - arg->flag_plus);
		else if (arg->precision == -1 && arg->flag_zero && s[0] == '-')
			l = ft_instart_x(&s, '0', arg->width - l);
	}
	if (arg->flag_plus && s[0] != '-')
		l = ft_instart_x(&s, '+', 1);
	if (arg->width > l)
		l = ft_instart_x(&s, ' ', arg->width - l);
	if (s && !arg->width && !arg->flag_plus && s[0] != '-' && arg->flag_space)
		l = ft_instart_x(&s, ' ', 1);
	ft_s_put(s);
}

void			ft_hhi_print(t_args *arg, va_list ap)
{
	int					l;
	char				*s;

	s = ft_itoa_base_x((char)va_arg(ap, int), 10);
	l = ft_strlen(s);
	ft_precision_x(&s, &l, arg);
	if (arg->width > (l))
	{
		if (arg->flag_minus)
			l = ft_inend_x(&s, ' ', arg->width - l - arg->flag_plus);
		else if (arg->precision == -1 && arg->flag_zero && s[0] != '-')
			l = ft_instart_x(&s, '0', arg->width - l - arg->flag_plus);
		else if (arg->precision == -1 && arg->flag_zero && s[0] == '-')
			l = ft_instart_x(&s, '0', arg->width - l);
	}
	if (arg->flag_plus && s[0] != '-')
		l = ft_instart_x(&s, '+', 1);
	if (arg->width > l)
		l = ft_instart_x(&s, ' ', arg->width - l);
	if (s && !arg->width && !arg->flag_plus && s[0] != '-' && arg->flag_space)
		l = ft_instart_x(&s, ' ', 1);
	ft_s_put(s);
}

void			ft_li_print(t_args *arg, va_list ap)
{
	int					l;
	char				*s;

	s = ft_itoa_base_x(va_arg(ap, long), 10);
	l = ft_strlen(s);
	ft_precision_x(&s, &l, arg);
	if (arg->width > (l))
	{
		if (arg->flag_minus)
			l = ft_inend_x(&s, ' ', arg->width - l - arg->flag_plus);
		else if (arg->precision == -1 && arg->flag_zero && s[0] != '-')
			l = ft_instart_x(&s, '0', arg->width - l - arg->flag_plus);
		else if (arg->precision == -1 && arg->flag_zero && s[0] == '-')
			l = ft_instart_x(&s, '0', arg->width - l);
	}
	if (arg->flag_plus && s[0] != '-')
		l = ft_instart_x(&s, '+', 1);
	if (arg->width > l)
		l = ft_instart_x(&s, ' ', arg->width - l);
	if (s && !arg->width && !arg->flag_plus && s[0] != '-' && arg->flag_space)
		l = ft_instart_x(&s, ' ', 1);
	ft_s_put(s);
}

void			ft_lli_print(t_args *arg, va_list ap)
{
	int					l;
	char				*s;

	s = ft_itoa_base_x(va_arg(ap, long long), 10);
	l = ft_strlen(s);
	ft_precision_x(&s, &l, arg);
	if (arg->width > (l))
	{
		if (arg->flag_minus)
			l = ft_inend_x(&s, ' ', arg->width - l - arg->flag_plus);
		else if (arg->precision == -1 && arg->flag_zero && s[0] != '-')
			l = ft_instart_x(&s, '0', arg->width - l - arg->flag_plus);
		else if (arg->precision == -1 && arg->flag_zero && s[0] == '-')
			l = ft_instart_x(&s, '0', arg->width - l);
	}
	if (arg->flag_plus && s[0] != '-')
		l = ft_instart_x(&s, '+', 1);
	if (arg->width > l)
		l = ft_instart_x(&s, ' ', arg->width - l);
	if (s && !arg->width && !arg->flag_plus && s[0] != '-' && arg->flag_space)
		l = ft_instart_x(&s, ' ', 1);
	ft_s_put(s);
}
