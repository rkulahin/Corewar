/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 14:45:06 by rkulahin          #+#    #+#             */
/*   Updated: 2019/02/17 13:54:13 by rkulahin         ###   ########.fr       */
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
	t_carriage		*tmp2;

	tmp = vm->carriage;
	while (tmp)
	{
		tmp2 = tmp;
		if ((tmp->live == -1) ||
			(tmp->live != -1 && tmp->live >= vm->cycle_to_die))
		{
			kill_carriage(vm, tmp);
			tmp = tmp2;
			continue ;
		}
		tmp->live = -1;
		tmp = tmp->next;
	}
	if (vm->live >= NBR_LIVE || vm->nbr_checks >= MAX_CHECKS)
	{
		vm->cycle_to_die -= CYCLE_DELTA;
		vm->nbr_checks = -1;
	}
	vm->live = 0;
	vm->cycle = 0;
	vm->nbr_checks++;
}

void	check_command(t_vm *vm, t_carriage *cr)
{
	int		i;

	i = vm_atoi_16(cr->operation);
	if (i > 0 && i <= 16)
	{
		g_func[i](vm, cr);
	}
	run_to_command(vm, cr);
}

void	main_cycle(t_vm *vm)
{
	int				check;
	t_carriage		*tmp;

	check = 1;
	while (check)
	{
		tmp = vm->carriage;
		if (vm->nbr_cycles >= vm->cycle)
			print_and_return();
		if (vm->cycle >= vm->cycle_to_die || vm->cycle_to_die <= 0)
			main_check(vm);
		if (!tmp)
			print_and_return();
		while (tmp)
		{
			if (tmp->cycle <= vm->cycle)
				check_command(vm, tmp);
			tmp = tmp->next;
		}
		vm->cycle++;
	}
}
