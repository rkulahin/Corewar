/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 14:45:06 by rkulahin          #+#    #+#             */
/*   Updated: 2019/02/25 14:31:10 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	kill_carriage(t_vm *vm, t_carriage *cr)
{
	t_carriage		*tmp;

	if ((vm->nbr_log & 8) == 8)
		ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
		cr->index, vm->cycle - cr->live, vm->cycle_to_die);
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
	if (i <= 0)
		win_player(last);
}

void	check_command(t_vm *vm, t_carriage *cr)
{
	int		i;
	int		old_pos;

	i = vm_atoi_16(cr->operation);
	if (i > 0 && i <= 16)
	{
		old_pos = cr->position;
		g_func[i - 1](vm, cr);
	// 		ft_printf("MAP :\n");
	// i = -1;
	// while (++i < MEM_SIZE * 2)
	// {
	// 	if ((i % 128) == 0)
	// 		ft_printf("\n");
	// 	if (i == 0 || i == 1)
	// 		ft_printf(RED"%c"EOC, vm->map[i]);
	// 	else if (i == (MEM_SIZE * 2) / vm->nbr_plrs || i == (MEM_SIZE * 2) / vm->nbr_plrs + 1)
	// 		ft_printf(YEL"%c"EOC, vm->map[i]);
	// 	else if (i == ((MEM_SIZE * 2) / vm->nbr_plrs) * 2 || i == ((MEM_SIZE * 2) / vm->nbr_plrs) * 2 + 1)
	// 		ft_printf(BLU"%c"EOC, vm->map[i]);
	// 	else if (i == ((MEM_SIZE * 2) / vm->nbr_plrs) * 3 || i == ((MEM_SIZE * 2) / vm->nbr_plrs) * 3 + 1)
	// 		ft_printf(GRE"%c"EOC, vm->map[i]);
	// 	else if (i <= 1225)
	// 		ft_printf(RED"%c"EOC, vm->map[i]);
	// 	else
	// 		ft_printf("%c", vm->map[i]);
	// }
	// ft_printf("\nsize = %d\n", i);
		if (vm->cycle == 1249)
			write(0, 0, 0);
		if (((vm->nbr_log & 16) == 16 && i != 9) ||
		((vm->nbr_log & 16) == 16 && cr->carry == 0 && i == 9))
		{
			ft_printf("ADV %d (%#.4x -> %#.4x) ",
			ABS((old_pos - cr->position) / 2), old_pos / 2, cr->position / 2);
			while (old_pos != cr->position)
			{
				ft_printf("%c%c ", vm->map[old_pos], vm->map[old_pos + 1]);
				old_pos = (old_pos + 2) % 8192;
			}
			ft_printf("\n");
		}
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
