/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 18:19:15 by rkulahin          #+#    #+#             */
/*   Updated: 2018/12/28 16:20:51 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_change_flag(int *i, int *index, int *flag)
{
	*flag = 1;
	*index += 1;
	*i = 1;
}

int		ft_find_flag(char const *str, t_args *arg, int index)
{
	int		i;

	i = 1;
	while (i != 0)
	{
		i = 0;
		if (str[index] == '-')
			ft_change_flag(&i, &index, &arg->flag_minus);
		if (str[index] == '+')
			ft_change_flag(&i, &index, &arg->flag_plus);
		if (str[index] == ' ')
			ft_change_flag(&i, &index, &arg->flag_space);
		if (str[index] == '#')
			ft_change_flag(&i, &index, &arg->flag_hash);
		if (str[index] == '0')
			ft_change_flag(&i, &index, &arg->flag_zero);
	}
	return (index);
}

int		ft_find_width(char const *str, t_args *arg, int index)
{
	int		i;
	int		tmp;
	char	*width;

	i = 0;
	if (str[index] >= '0' && str[index] <= '9')
	{
		tmp = i;
		while (str[i + index] >= '0' && str[i + index] <= '9')
			i++;
		index += i;
		width = malloc(sizeof(char) * (i));
		while (tmp < i)
		{
			width[tmp] = str[index - i + tmp];
			tmp++;
		}
		width[tmp] = '\0';
		arg->width = ft_atoi(width);
		free(width);
	}
	return (index);
}

int		ft_find_precision(char const *str, t_args *arg, int index)
{
	int		i;
	int		tmp;
	char	*precision;

	i = 1;
	if (str[index] == '.')
	{
		tmp = 0;
		while (str[i + index] >= '0' && str[i + index] <= '9')
			i++;
		index += i;
		precision = malloc(sizeof(char) * (i));
		while (tmp < i - 1)
		{
			precision[tmp] = str[index - i + tmp + 1];
			tmp++;
		}
		precision[tmp] = '\0';
		arg->precision = ft_atoi(precision);
		free(precision);
		if (arg->precision == 0)
			return (index);
	}
	return (index);
}

int		ft_find_modifiers(char const *str, t_args *arg, int index)
{
	if (str[index] == 'h' && str[index + 1] == 'h')
		ft_change_mod(2, &index, &arg->modifiers, 2);
	else if (str[index] == 'h')
		ft_change_mod(1, &index, &arg->modifiers, 1);
	else if (str[index] == 'l' && str[index + 1] == 'l')
		ft_change_mod(2, &index, &arg->modifiers, 4);
	else if (str[index] == 'l')
		ft_change_mod(1, &index, &arg->modifiers, 3);
	else if (str[index] == 'L')
		ft_change_mod(1, &index, &arg->modifiers, 5);
	return (index);
}
