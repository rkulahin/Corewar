/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_x.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 10:14:31 by rkulahin          #+#    #+#             */
/*   Updated: 2018/12/27 16:09:58 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int				ft_instart_x(char **s, int c, int l)
{
	char	*ptr;
	char	*del;

	ptr = ft_strnew(l);
	ptr = ft_memset(ptr, c, l);
	del = *s;
	if (!*s)
		*s = ft_strjoin(ptr, "");
	else if (c == '0' && **s == '-')
	{
		*s = ft_strjoin(ptr, (*s + 1));
		ft_instart_x(s, '-', 1);
	}
	else
		*s = ft_strjoin(ptr, *s);
	free(ptr);
	free(del);
	return (ft_strlen(*s));
}

int				ft_inend_x(char **s, int c, int l)
{
	char	*ptr;
	char	*del;

	ptr = ft_strnew(l);
	ptr = ft_memset(ptr, c, l);
	del = *s;
	if (!*s)
		*s = ft_strjoin("", ptr);
	else
		*s = ft_strjoin(*s, ptr);
	free(ptr);
	free(del);
	return (ft_strlen(*s));
}

void			ft_precision_x(char **s, int *l, t_args *arg)
{
	char *s1;

	if ((arg->precision >= *l && **s == '-') || (arg->precision > *l))
	{
		*l = ft_instart_x(s, '0', arg->precision - *l);
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

void			ft_x_mod(t_args *arg, va_list ap, int *index)
{
	index[0] += 1;
	if (arg->modifiers == 1)
		ft_hx_print(arg, ap);
	else if (arg->modifiers == 2)
		ft_hhx_print(arg, ap);
	else if (arg->modifiers == 3)
		ft_lx_print(arg, ap);
	else if (arg->modifiers == 4)
		ft_llx_print(arg, ap);
	else
		ft_x_print(arg, ap);
}

void			ft_x_print(t_args *arg, va_list ap)
{
	int					l;
	char				*s;

	s = ft_itoa_base_x(va_arg(ap, unsigned int), 16);
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
