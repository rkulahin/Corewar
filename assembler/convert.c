/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshreder <vshreder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 15:00:08 by yyakoven          #+#    #+#             */
/*   Updated: 2019/03/22 18:15:51 by vshreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void					fill_two_boyz(t_instr *instr, unsigned char *arr,
						int fd_cor, int i)
{
	short				any_s;
	unsigned short		c;

	any_s = ft_atoi(instr->args[i]);
	if (any_s < 0)
		c = (unsigned short)any_s;
	else
		c = any_s;
	c = reverse_short(c);
	*(short*)arr = c;
	write(fd_cor, arr, 2);
	arr += sizeof(short);
}

void					fill_four_boyz(t_instr *instr, unsigned char *arr,
	int fd_cor, int i)
{
	unsigned int		b;
	int					any;

	any = ft_atoi(instr->args[i]);
	if (any < 0)
		b = (unsigned int)any;
	else
		b = any;
	b = reverse_int(b);
	*(int*)arr = b;
	write(fd_cor, arr, 4);
	arr += sizeof(int);
}

void					fill_args(t_instr *instr, unsigned char *arr,
						int fd_cor)
{
	int					i;

	i = 0;
	while (i < g_optab[instr->code - 1].num_arg)
	{
		if (instr->arg_codes[i] == 1)
		{
			*arr = ft_atoi(instr->args[i]);
			write(fd_cor, arr, 1);
			arr++;
		}
		else if ((instr->arg_codes[i] == IND_CODE) ||
			(instr->arg_codes[i] == DIR_CODE
		&& g_optab[instr->code - 1].carry == T_DIR))
			fill_two_boyz(instr, arr, fd_cor, i);
		else if (instr->arg_codes[i] != 0)
			fill_four_boyz(instr, arr, fd_cor, i);
		i++;
	}
}

void					fill_data(t_instr *instr, unsigned char *arr,
						int fd_cor)
{
	*arr = instr->code;
	write(fd_cor, arr, 1);
	arr++;
	if (g_optab[instr->code - 1].codage)
	{
		*arr = 0 + (instr->arg_codes[0] << 6);
		*arr += (instr->arg_codes[1] << 4);
		*arr += (instr->arg_codes[2] << 2);
		write(fd_cor, arr, 1);
		arr++;
	}
	fill_args(instr, arr, fd_cor);
}

void					encode(t_instr *instr, int fd_cor)
{
	unsigned char		*arr;
	int					i;

	i = 0;
	while (instr)
	{
		arr = (unsigned char *)malloc(sizeof(char) * instr->bytes);
		fill_data(instr, arr, fd_cor);
		instr = instr->next;
		free(arr);
	}
}
