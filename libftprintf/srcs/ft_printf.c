/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 13:00:27 by rkulahin          #+#    #+#             */
/*   Updated: 2018/12/22 15:21:03 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

t_args	*ft_arg_inf(char const *str, int *index)
{
	t_args	*arg;

	arg = malloc(sizeof(t_args));
	*arg = (t_args){0, 0, 0, 0, 0, 0, -1, 0};
	index[0] = ft_find_flag(str, arg, index[0]);
	index[0] = ft_find_width(str, arg, index[0]);
	index[0] = ft_find_precision(str, arg, index[0]);
	index[0] = ft_find_modifiers(str, arg, index[0]);
	return (arg);
}

int		ft_printf(char	const *str, ...)
{
	va_list ap;
	int		index;
	t_args	*arg;

	va_start(ap, str);
	g_ret = 0;
	index = 0;
	if (ft_strcmp(str, "%") == 0)
	{
		return (0);
	}
	while ((index = ft_find_arg(str, index)) != -1)
	{
		arg = ft_arg_inf(str, &index);
		ft_arg_print(arg, str, &index, ap);
		free(arg);
	}
	va_end(ap);
	return (g_ret);
}
