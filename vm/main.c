/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 14:34:35 by rkulahin          #+#    #+#             */
/*   Updated: 2019/03/14 14:15:27 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_players		*init_player(void)
{
	t_players	*new;

	new = (t_players *)malloc(sizeof(t_players));
	new->champ = NULL;
	new->index = 1;
	new->live = -1;
	new->next = NULL;
	return (new);
}

t_vm			*init_vm(void)
{
	t_vm	*new;

	new = (t_vm *)malloc(sizeof(t_vm));
	new->players = NULL;
	new->last_name = NULL;
	new->last_index = -1;
	new->carriage = NULL;
	ft_bzero(new->index_player, sizeof(int) * 4);
	new->nbr_cycles = 0;
	new->cycle = 0;
	new->live = 0;
	new->curses = 0;
	new->nbr_log = 0;
	new->nbr_checks = 1;
	new->nbr_car = 1;
	new->aff = 0;
	new->cycle_to_die = CYCLE_TO_DIE;
	new->die = CYCLE_TO_DIE;
	return (new);
}

void			error(char *line)
{
	ft_printf("%s\n", line);
	system("Leaks virtual_machine");
	exit(1);
}

unsigned int	reverse(unsigned int b)
{
	b = (b >> 16 | b << 16);
	b = ((b & 0xFF00FF00) >> 8 | (b & 0x00FF00FF) << 8);
	return (b);
}

int				main(int ac, char **av)
{
	t_vm	*all;

	all = parce_argv(ac, av, 1);
	if (all->nbr_plrs >= 5)
		error("TOO_MANY_PLAYERS");
	if (all->nbr_plrs <= 0)
		print_usage();
	if (all->curses == 1)
		null_flags(all);
	ft_memset(all->map, '0', MEM_SIZE * 2);
	ft_memset(all->color, 0, MEM_SIZE * 2);
	vm_map(all, all->players, 0, 0);
	privetstvie(all);
	main_cycle(all);
	return (0);
}
