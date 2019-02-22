/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 14:45:06 by rkulahin          #+#    #+#             */
/*   Updated: 2019/02/22 11:19:35 by rkulahin         ###   ########.fr       */
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

void	main_check(t_vm *vm, t_carriage *tmp)
{
	t_carriage		*tmp2;

	check_player(vm);
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
	vm->cycle_to_die = vm->cycle_to_die + vm->cycle;
	vm->nbr_checks++;
}

void	check_player(t_vm *vm)
{
	t_players	*tmp;
	t_players	*last;
	int			i;

	i = 0;
	last = vm->players;
	tmp = vm->players;
	while (tmp)
	{
		if (i == 0 && tmp->live > last->live)
			last = tmp;
		if (tmp->live != -1 && tmp->live > vm->cycle - vm->cycle_to_die
			&& tmp->live < vm->cycle)
		{
			last = tmp;
			i++;
		}
		tmp->live = -1;
		tmp = tmp->next;
	}
	if (i <= 1)
		win_player(last);
}

void	check_command(t_vm *vm, t_carriage *cr)
{
	int		i;

	i = vm_atoi_16(cr->operation);
	if (i > 0 && i <= 17)
	{
		g_func[i - 1](vm, cr);
	}
	run_to_command(vm, cr);
}

void	main_cycle(t_vm *vm)
{
	int				check;
	t_carriage		*car;

	check = 1;
	while (check)
	{
		car = vm->carriage;
		if (vm->nbr_cycles >= vm->cycle && vm->nbr_cycles != 0)
			print_and_return();
		if (vm->cycle >= vm->cycle_to_die)
			main_check(vm, NULL);
		if (!car)
			print_and_return();
		while (car)
		{
			if (car->cycle <= vm->cycle)
				check_command(vm, car);
			car = car->next;
		}
		if ((vm->nbr_log & 2) == 2)
			ft_printf("It is now cycle %i\n", vm->cycle + 1);
		vm->cycle++;
	}
}
