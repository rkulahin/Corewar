/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_o_mod.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 15:27:07 by rkulahin          #+#    #+#             */
/*   Updated: 2018/12/28 10:39:55 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void			ft_ho_print(t_args *arg, va_list ap)
{
	int					l;
	char				*s;

	s = ft_itoa_base_x_u((unsigned short)va_arg(ap, unsigned int), 8);
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

void			ft_hho_print(t_args *arg, va_list ap)
{
	int					l;
	char				*s;

	s = ft_itoa_base_x_u((unsigned char)va_arg(ap, unsigned int), 8);
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

void			ft_lo_print(t_args *arg, va_list ap)
{
	int					l;
	char				*s;

	s = ft_itoa_base_x_u(va_arg(ap, unsigned long), 8);
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

void			ft_llo_print(t_args *arg, va_list ap)
{
	int					l;
	char				*s;

	s = ft_itoa_base_x_u(va_arg(ap, unsigned long long), 8);
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
