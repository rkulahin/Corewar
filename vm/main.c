/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seshevch <seshevch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 14:34:35 by rkulahin          #+#    #+#             */
/*   Updated: 2019/02/25 18:23:04 by seshevch         ###   ########.fr       */
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
	new->nbr_log = 0;
	new->nbr_car = 1;
	new->cycle_to_die = CYCLE_TO_DIE;
	new->die = CYCLE_TO_DIE;
	return (new);
}

void			error(char *line)
{
	ft_printf("%s\n", line);
	exit(1);
}

unsigned int	reverse(unsigned int b)
{
	b = (b >> 16 | b << 16);
	b = ((b & 0xFF00FF00) >> 8 | (b & 0x00FF00FF) << 8);
	return (b);
}

void			test(t_vm *all)
{
	int			i;
	t_players	*tmp;
	t_carriage	*tmp2;

	tmp = all->players;
	tmp2 = all->carriage;
	ft_printf("nbr_cycles: %i\n", all->nbr_cycles);
	ft_printf("nbr_players: %i\n", all->nbr_plrs);
	ft_printf("nbr_index[0]: %i\n", all->index_player[0]);
	ft_printf("nbr_index[1]: %i\n", all->index_player[1]);
	ft_printf("nbr_index[2]: %i\n", all->index_player[2]);
	ft_printf("nbr_index[3]: %i\n", all->index_player[3]);
	while (tmp)
	{
		ft_printf("index_champ: %i\n", tmp->index);
		ft_printf("champ_magic: %#x\n", tmp->champ->magic);
		ft_printf("champ_name: %s\n", tmp->champ->prog_name);
		ft_printf("champ_comment: %s\n", tmp->champ->comment);
		tmp = tmp->next;
	}
	ft_printf("MAP :\n");
	i = -1;
	while (++i < MEM_SIZE * 2)
	{
		if (i == 0 || i == 1)
			ft_printf(RED"%c"EOC, all->map[i]);
		else if (i == (MEM_SIZE * 2) / all->nbr_plrs || i == (MEM_SIZE * 2) / all->nbr_plrs + 1)
			ft_printf(YEL"%c"EOC, all->map[i]);
		else if (i == ((MEM_SIZE * 2) / all->nbr_plrs) * 2 || i == ((MEM_SIZE * 2) / all->nbr_plrs) * 2 + 1)
			ft_printf(BLU"%c"EOC, all->map[i]);
		else if (i == ((MEM_SIZE * 2) / all->nbr_plrs) * 3 || i == ((MEM_SIZE * 2) / all->nbr_plrs) * 3 + 1)
			ft_printf(GRE"%c"EOC, all->map[i]);
		else
			ft_printf("%c", all->map[i]);
	}
	ft_printf("\nsize = %d\n", i);
	while (tmp2)
	{
		ft_printf("nbr_plr:%i\n", tmp2->nbr_plr);
		ft_printf("regist:%x\n", tmp2->regist[0]);
		ft_printf("cycle:%i\n", tmp2->cycle);
		tmp2 = tmp2->next;
	}
	int *arr;
	arr = check_arg(0x90);
	ft_printf("%i\n", arr[0]);
	ft_printf("%i\n", arr[1]);
	ft_printf("%i\n", arr[2]);
	ft_printf("%i\n", g_optab[6].args[0]);
	int f;
	f = (short)32767;
	ft_printf("%i", f);
}

int				main(int ac, char **av)
{
	t_vm	*all;

	all = parce_argv(ac, av);
	ft_memset(all->map, '0', MEM_SIZE * 2);
	vm_map(all, all->players, 0, 0);
	main_cycle(all);
	// test(all);
	return (0);
}
