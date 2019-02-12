/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_s.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 17:51:57 by rkulahin          #+#    #+#             */
/*   Updated: 2018/12/28 18:23:31 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void		custom_s(int *len, t_args *arg, char **ptr, char **str)
{
	*len = arg->width - ft_strlen(*ptr);
	if ((!arg->flag_zero) || (arg->flag_zero && arg->flag_minus))
		*str = ft_memset(ft_strnew(*len), ' ', *len);
	else
		*str = ft_memset(ft_strnew(*len), '0', *len);
}

void			ft_s_p(char *str, char *ptr)
{
	ft_s_put(str);
	ft_s_put(ptr);
}

void			ft_s_put(char *str)
{
	if (str != NULL && str[0] != '\0')
	{
		ft_putstr(str);
		g_ret += ft_strlen(str);
		free(str);
	}
}

void			ft_s_print(t_args *arg, va_list ap, int *index)
{
	char	*str;
	char	*ptr;
	int		i;
	int		len;

	index[0] += 1;
	i = 0;
	str = va_arg(ap, char *);
	if (str == NULL)
		str = "(null)";
	if (arg->precision == (-1) || ft_strcmp(str, "") == 0)
		arg->precision = ft_strlen(str);
	ptr = ft_strnew(arg->precision);
	ptr = ft_strncpy(ptr, str, arg->precision);
	if (arg->width > (int)ft_strlen(ptr))
	{
		custom_s(&len, arg, &ptr, &str);
		if (arg->flag_minus == 1)
		{
			ft_s_p(ptr, str);
			return ;
		}
		ft_s_put(str);
	}
	ft_s_put(ptr);
}
