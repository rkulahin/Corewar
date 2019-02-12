/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_u_mod.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 12:27:06 by rkulahin          #+#    #+#             */
/*   Updated: 2018/12/27 12:28:34 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void			ft_hu_print(t_args *arg, va_list ap)
{
	int					l;
	char				*s;

	s = ft_itoa_base_x_u((unsigned short)va_arg(ap, unsigned int), 10);
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

void			ft_hhu_print(t_args *arg, va_list ap)
{
	int					l;
	char				*s;

	s = ft_itoa_base_x_u((unsigned char)va_arg(ap, unsigned int), 10);
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

void			ft_lu_print(t_args *arg, va_list ap)
{
	int					l;
	char				*s;

	s = ft_itoa_base_x_u(va_arg(ap, unsigned long int), 10);
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

void			ft_llu_print(t_args *arg, va_list ap)
{
	int					l;
	char				*s;

	s = ft_itoa_base_x_u(va_arg(ap, unsigned long long int), 10);
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
