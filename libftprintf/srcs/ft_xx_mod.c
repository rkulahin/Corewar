/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xx_mod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 11:23:27 by rkulahin          #+#    #+#             */
/*   Updated: 2018/12/28 16:02:50 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void			ft_hxx_print(t_args *arg, va_list ap)
{
	int					l;
	char				*s;

	s = ft_itoa_base_xx_u((unsigned short)va_arg(ap, unsigned int), 16);
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

void			ft_hhxx_print(t_args *arg, va_list ap)
{
	int					l;
	char				*s;

	s = ft_itoa_base_xx_u((unsigned char)va_arg(ap, unsigned int), 16);
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

void			ft_lxx_print(t_args *arg, va_list ap)
{
	int					l;
	char				*s;

	s = ft_itoa_base_xx_u(va_arg(ap, unsigned long int), 16);
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
		l = ft_instart_x(&s, 'x', 1);
		l = ft_instart_x(&s, '0', 1);
	}
	if (arg->width > l)
		l = ft_instart_x(&s, ' ', arg->width - l);
	ft_s_put(s);
}

void			ft_llxx_print(t_args *arg, va_list ap)
{
	int					l;
	char				*s;

	s = ft_itoa_base_xx_u(va_arg(ap, unsigned long long int), 16);
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
