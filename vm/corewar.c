/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 14:45:06 by rkulahin          #+#    #+#             */
/*   Updated: 2019/03/17 11:18:30 by rkulahin         ###   ########.fr       */
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
		free(cr);
		return ;
	}
	while (tmp)
	{
		if (tmp->next && tmp->next->index == cr->index)
		{
			tmp->next = cr->next;
			free(cr);
			return ;
		}
		tmp = tmp->next;
	}
	free(cr);
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
	if (last->live < vm->cycle - vm->die && vm->curses != 1)
		win_player(last);
}

void			print_adv16(t_vm *vm, t_carriage *cr, int old_pos, int i)
{
	int		move;
	int		k;

	if (((vm->nbr_log & 16) == 16 && i != 9) ||
		((vm->nbr_log & 16) == 16 && cr->carry == 0 && i == 9))
	{
		if (cr->position < old_pos)
			move = ABS(((8192 - old_pos) + cr->position) / 2);
		else
			move = ABS((cr->position - old_pos) / 2);
		ft_printf("ADV %d (%#.4x -> %#.4x) ",
		move, (old_pos + 1) / 2, (cr->position + 1) / 2);
		k = -1;
		while (++k < move)
		{
			ft_printf("%c%c ", vm->map[old_pos % 8192],
			vm->map[(old_pos + 1) % 8192]);
			old_pos = (old_pos + 2) % 8192;
		}
		ft_printf("\n");
	}
}

void			check_command(t_vm *vm, t_carriage *cr)
{
	int		i;
	int		old_pos;

	cr->position = cr->position % 8192;
	i = vm_atoi_16(cr->operation);
	if (i > 0 && i <= 16)
	{
		old_pos = cr->position;
		g_func[i - 1](vm, cr);
		print_adv16(vm, cr, old_pos, i);
	}
	else
		cr->position = (cr->position + 2) % 8192;
	cr->cycle = -1;
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

void			main_cycle(t_vm *vm)
{
	t_carriage		*car;
	int				vis;

	vis = 1;
	if (vm->curses == 1)
	{
		init_curses();
		visual_map(vm);
		print_cr(vm);
	}
	while (true)
	{
		if (vis == 1)
		{	
		car = vm->carriage;
		if (vm->nbr_cycles >= vm->cycle && vm->nbr_cycles != 0)
			print_dump(vm);
		if (!car)
			print_dump(vm);
		while (car)
		{
			if (car->cycle <= vm->cycle)
			{
				delete_cr(vm);
				if (car->cycle != -1)
					check_command(vm, car);
				else if (!check_new_command(vm, car))
					car->position = (car->position + 2) % 8192;
				print_cr(vm);
			}
			car = car->next;
		}
		if (vm->cycle >= vm->cycle_to_die)
			main_check(vm, NULL);
		print_cycle(vm);
		vm->cycle++;
		}
		visual_menu(vm);
		if (vm->cycle >= 10000 && vis == 1)
			vis = 0;
		if (getch() == KEY_UP)
			vis = vis == 1 ? 0 : 1;
	}
	endwin();
}