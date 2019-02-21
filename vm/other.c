/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 16:09:17 by rkulahin          #+#    #+#             */
/*   Updated: 2019/02/21 15:18:59 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		win_player(t_players *last)
{
	t_players *tmp;

	tmp = last;
	ft_printf("\nPEREMOGA\n");
	exit(1);
}

void		print_and_return(void)
{
	return ;
}

void		run_to_command(t_vm *vm, t_carriage *cr)
{
	int		check;
	int		i;

	check = 1;
	while (check)
	{
		cr->position = cr->position % 8192;
		cr->operation[0] = cr->position;
		cr->operation[1] = (cr->position + 1) % 8192;
		i = vm_atoi_16(cr->operation);
		if (i >= 1 && i <= 16)
			break ;
		cr->position += 2;
	}
	cr->cycle = g_optab[i].num_cycle + vm->cycle;
}
