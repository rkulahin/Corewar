/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 13:53:35 by rkulahin          #+#    #+#             */
/*   Updated: 2018/12/30 11:45:25 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_bonus(char const *str, t_args *arg, va_list ap, int *i)
{
	if (str[i[0]] == 'U')
		ft_lu_print(arg, ap);
	else if (str[i[0]] == 'O')
		ft_lo_print(arg, ap);
	else if (str[i[0]] == 'D')
		ft_li_print(arg, ap);
	i[0]++;
}

void	free_line(char *str)
{
	if (str != NULL)
		free(str);
}

int		ft_find_arg(char const *str, int index)
{
	while (str[index])
	{
		if (str[index] == '%' && str[index + 1] == '%')
		{
			write(1, &str[index], 1);
			g_ret++;
			index += 2;
		}
		else if (str[index] == '%')
		{
			return (index + 1);
		}
		else
		{
			write(1, &str[index], 1);
			g_ret++;
			index++;
		}
	}
	return (-1);
}

void	ft_arg_print(t_args *arg, char const *str, int *i, va_list ap)
{
	if (str[i[0]] == 's' || str[i[0]] == 'S')
		ft_s_print(arg, ap, i);
	else if (str[i[0]] == 'c' || str[i[0]] == 'C')
		ft_c_print(arg, ap, i);
	else if (str[i[0]] == 'p')
		ft_p_print(arg, ap, i);
	else if (str[i[0]] == 'x')
		ft_x_mod(arg, ap, i);
	else if (str[i[0]] == 'u')
		ft_u_mod(arg, ap, i);
	else if (str[i[0]] == 'X')
		ft_xx_mod(arg, ap, i);
	else if (str[i[0]] == 'o')
		ft_o_mod(arg, ap, i);
	else if (str[i[0]] == 'O' || str[i[0]] == 'U' || str[i[0]] == 'D')
		ft_bonus(str, arg, ap, i);
	else if (str[i[0]] == 'i' || str[i[0]] == 'd')
		ft_i_mod(arg, ap, i);
	else
		ft__print(arg, i, str);
}

void	ft_change_mod(int i, int *index, int *flag, int num_mod)
{
	*flag = num_mod;
	*index += i;
}
