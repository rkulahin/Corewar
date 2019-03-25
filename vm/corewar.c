/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 14:45:06 by rkulahin          #+#    #+#             */
/*   Updated: 2019/03/25 12:38:15 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			change_cycle(t_vm *vm)
{
	if (vm->live >= NBR_LIVE || vm->nbr_checks >= MAX_CHECKS)
	{
		vm->die -= CYCLE_DELTA;
		vm->nbr_checks = 0;
	}
	vm->live = 0;
	if (vm->die <= 0)
		vm->cycle_to_die += 1;
	else
		vm->cycle_to_die = vm->cycle + vm->die;
}

static	void	print_cycle(t_vm *vm)
{
	if (((vm->nbr_checks == 1) && (((vm->nbr_log & 2) == 2) &&
	((vm->cycle_to_die - vm->cycle == vm->die && vm->cycle != 0) ||
	vm->die < 0))) && (vm->die != CYCLE_TO_DIE))
		ft_printf("Cycle to die is now %i\n", vm->die);
	if ((vm->nbr_log & 2) == 2)
		ft_printf("It is now cycle %i\n", vm->cycle + 1);
}

int				check_new_command(t_vm *vm, t_carriage *cr)
{
	int		i;

	cr->position = cr->position % 8192;
	cr->operation[0] = vm->map[cr->position % 8192];
	cr->operation[1] = vm->map[(cr->position + 1) % 8192];
	i = (unsigned char)vm_atoi_16(cr->operation);
	if (i >= 1 && i <= 16)
	{
		cr->cycle = g_optab[i - 1].num_cycle + vm->cycle - 1;
		return (1);
	}
	else
	{
		cr->cycle = -1;
		return (0);
	}
}

static void		main_cycle_car(t_vm *vm, t_carriage *car)
{
	while (car)
	{
		if (car->cycle <= vm->cycle)
		{
			if (vm->curses == 1)
				delete_cr(vm);
			if (car->cycle != -1)
				check_command(vm, car);
			else if (!check_new_command(vm, car))
				car->position = (car->position + 2) % 8192;
			if (vm->curses == 1)
				print_cr(vm);
		}
		car = car->next;
	}
}

void			main_cycle(t_vm *vm)
{
	t_carriage		*car;
	int				vis;

	vis = 0;
	print_cycle(vm);
	while (true)
	{
		vis = control_curses(vis, vm, 0);
		if (vis != 0 || vm->curses == 0)
		{
			vm->cycle++;
			car = vm->carriage;
			main_cycle_car(vm, car);
			if (vm->cycle >= vm->cycle_to_die)
				main_check(vm, NULL);
			if (vm->nbr_cycles == vm->cycle && vm->nbr_cycles != 0)
				print_dump(vm);
			print_cycle(vm);
		}
	}
}
