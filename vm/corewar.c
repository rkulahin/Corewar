/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 14:45:06 by rkulahin          #+#    #+#             */
/*   Updated: 2019/02/16 18:34:36 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	kill_carriage(t_vm *vm, t_carriage *cr)
{
	t_carriage		*tmp;

	tmp = vm->carriage;
	if (tmp && tmp == cr)
	{
		vm->carriage = cr->next;
		free(cr);
		return ;
	}
	while (tmp)
	{
		if (tmp->next && tmp->next == cr)
		{
			tmp->next = cr->next;
			free(cr);
			return ;
		}
		tmp = tmp->next;
	}
}

void	main_check(t_vm *vm)
{
	t_carriage		*tmp;

	tmp = vm->carriage;
	while (tmp)
	{
		tmp2 = tmp;
		if (tmp->live == -1 || (tmp->live != -1 && tmp->live >= CYCLE_TO_DIE))
		{
			kill_carriage(vm, tmp);
			tmp = tmp2;
			continue ;
		}
		tmp->live = -1;
		tmp = tmp->next;
	}
	if (vm->live >= NBR_LIVE || vm->nbr_checks >= MAX_CHECKS)
		CYCLE_TO_DIE -= CYCLE_DELTA;
	
}

void	main_cycle(t_vm *vm)
{
	int				check;
	t_carriage		*tmp;

	check = 1;
	while (check)
	{
		tmp = vm->carriage;
		if (vm->nbr_cycles >= CYCLE_TO_DIE)
			print_and_return();
		if (vm->cycle >= CYCLE_TO_DIE || CYCLE_TO_DIE <= 0)
			main_check(vm);
		if (!tmp)
			print_and_return();
		while (tmp)
		{
			if (tmp->cycle <= vm->nbr_cycles)
				check_command(vm, tmp);
			tmp = tmp->next;
		}
		vm->nbr_cycles++;
	}
}
