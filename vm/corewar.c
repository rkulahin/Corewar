/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 14:45:06 by rkulahin          #+#    #+#             */
/*   Updated: 2019/03/04 16:08:31 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			kill_carriage(t_vm *vm, t_carriage *cr)
{
	t_carriage		*tmp;

	if ((vm->nbr_log & 8) == 8)
		ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
		cr->index, vm->cycle_to_die - cr->live, vm->die);
	tmp = vm->carriage;
	if (!cr->next)
		cr->next = NULL;
	if (tmp && tmp->index == cr->index)
	{
		vm->carriage = cr->next;
		return ;
	}
	while (tmp)
	{
		if (tmp->next && tmp->next->index == cr->index)
		{
			tmp->next = cr->next;
			return ;
		}
		tmp = tmp->next;
	}
}

static void		change_cycle(t_vm *vm)
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

void			main_check(t_vm *vm, t_carriage *tmp)
{
	t_carriage		*tmp2;

	tmp = vm->carriage;
	while (tmp)
	{
		tmp2 = tmp->next;
		if (tmp->live <= vm->cycle_to_die - vm->die)
		{
			if (tmp->live < 0)
				tmp->live += 1;
			kill_carriage(vm, tmp);
			tmp = tmp2;
		}
		else
			tmp = tmp->next;
	}
	change_cycle(vm);
	if (!vm->carriage)
		check_player(vm);
	vm->nbr_checks += 1;
}

void			check_player(t_vm *vm)
{
	t_players	*tmp;
	t_players	*last;

	last = vm->players;
	tmp = vm->players;
	while (tmp)
	{
		if (tmp->live > last->live)
			last = tmp;
		tmp = tmp->next;
	}
	if (last->live < vm->cycle - vm->die)
		win_player(last);
}

void			check_command(t_vm *vm, t_carriage *cr, int j)
{
	int		i;
	int		old_pos;

	i = vm_atoi_16(cr->operation);
	if (i > 0 && i <= 16)
	{
		j = 1;
		old_pos = cr->position;
		g_func[i - 1](vm, cr);
		if (((vm->nbr_log & 16) == 16 && i != 9) ||
		((vm->nbr_log & 16) == 16 && cr->carry == 0 && i == 9))
		{
			ft_printf("ADV %d (%#.4x -> %#.4x) ",
			ABS((old_pos - cr->position) / 2), old_pos / 2, cr->position / 2);
			while (old_pos != cr->position)
			{
				ft_printf("%c%c ", vm->map[old_pos % 8192],
				vm->map[(old_pos + 1) % 8192]);
				old_pos = (old_pos + 2) % 8192;
			}
			ft_printf("\n");
		}
	}
	// run_to_command(vm, cr, j);
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

static void		check_new_command(t_vm *vm, t_carriage *cr)
{
	int		i;

	if (cr->cycle == -1)
		cr->position = (cr->position + 2) % 8192;
	cr->operation[0] = vm->map[cr->position % 8192];
	cr->operation[1] = vm->map[(cr->position + 1) % 8192];
	i = (unsigned char)vm_atoi_16(cr->operation);
	if (i >= 1 && i <= 16)
		cr->cycle = g_optab[i - 1].num_cycle + vm->cycle;
	else
		cr->cycle = -1;
}

void			main_cycle(t_vm *vm)
{
	int				check;
	t_carriage		*car;
	// int				i;

	check = 1;
	while (check)
	{
		car = vm->carriage;
		if (vm->cycle == 25368)
			write(0, 0, 0);
		if (vm->nbr_cycles >= vm->cycle && vm->nbr_cycles != 0)
			print_and_return();
		if (!car)
			print_and_return();
		while (car)
		{
			if (car->cycle <= vm->cycle && car->cycle != -1)
				check_command(vm, car, 0);
			car = car->next;
		}
		car = vm->carriage;
		while (car)
		{
			if (car->cycle <= vm->cycle)
				check_new_command(vm, car);
			car = car->next;
		}
		if (vm->cycle >= vm->cycle_to_die)
			main_check(vm, NULL);
		print_cycle(vm);
		vm->cycle++;
	}
}

				// 	ft_printf("Cycle %i\nMAP :\n", vm->cycle);
				// 	i = -1;
				// 	while (++i < MEM_SIZE * 2)
				// 	{
				// 		if (i % 128 == 0)
				// 			ft_printf("\n");
				// 		if (i == car->position)
				// 			ft_printf(GRE"L"EOC);
				// 		if (i == 0 || i == 1)
				// 			ft_printf(RED"%c"EOC, vm->map[i]);
				// 		else if (i == (MEM_SIZE * 2) / vm->nbr_plrs || i == (MEM_SIZE * 2) / vm->nbr_plrs + 1)
				// 			ft_printf(YEL"%c"EOC, vm->map[i]);
				// 		else if (i == ((MEM_SIZE * 2) / vm->nbr_plrs) * 2 || i == ((MEM_SIZE * 2) / vm->nbr_plrs) * 2 + 1)
				// 			ft_printf(BLU"%c"EOC, vm->map[i]);
				// 		else if (i == ((MEM_SIZE * 2) / vm->nbr_plrs) * 3 || i == ((MEM_SIZE * 2) / vm->nbr_plrs) * 3 + 1)
				// 			ft_printf(GRE"%c"EOC, vm->map[i]);
				// 		else
				// 			ft_printf("%c", vm->map[i]);
				// 	}
				// 	ft_printf("\nsize = %d\n", i);
				// 	}