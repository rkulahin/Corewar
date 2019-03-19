/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 16:36:52 by rkulahin          #+#    #+#             */
/*   Updated: 2019/03/19 16:05:04 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			kill_carriage(t_vm *vm, t_carriage **cr)
{
	t_carriage		*prev;
	t_carriage		*next;

	if ((vm->nbr_log & 8) == 8)
		ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
		(*cr)->index, vm->cycle_to_die - (*cr)->live, vm->die);
	prev = (*cr)->prev;
	next = (*cr)->next;
	if (!prev && next)
	{
		vm->carriage = next;
		next->prev = NULL;
	}
	else if (!next && prev)
		prev->next = next;
	else if (prev && next)
	{
		prev->next = next;
		next->prev = prev;
	}
	else
		vm->carriage = NULL;
	free(*cr);
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
			kill_carriage(vm, &tmp);
			tmp = tmp2;
		}
		else
			tmp = tmp->next;
	}
	change_cycle(vm);
	if (vm->cycle == 28000)
		write(0, 0, 0);
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
		if (tmp->live > last->live ||
		(tmp->live == last->live && tmp->index < last->index))
			last = tmp;
		tmp = tmp->next;
	}
	if ((last->live < vm->cycle - vm->die && vm->die > 0) ||
	(last->live < vm->cycle && vm->die < 0))
		win_player(vm, last);
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
