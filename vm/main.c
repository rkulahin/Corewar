/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 14:34:35 by rkulahin          #+#    #+#             */
/*   Updated: 2019/02/14 13:25:49 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_players		*init_player(void)
{
	t_players	*new;

	new = (t_players *)malloc(sizeof(t_players));
	new->champ = NULL;
	new->index = 1;
	new->next = NULL;
	return (new);
}

t_vm			*init_vm(void)
{
	t_vm	*new;

	new = (t_vm *)malloc(sizeof(t_vm));
	new->champs = NULL;
	new->carriage = NULL;
	ft_bzero(new->index_player, 32);
	new->nbr_cycles = 0;
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

	tmp = all->champs;
	ft_printf("nbr_cycles: %i\n", all->nbr_cycles);
	ft_printf("nbr_champs: %i\n", all->nbr_plrs);
	ft_printf("nbr_index[0]: %i\n", all->index_player[0]);
	ft_printf("nbr_index[1]: %i\n", all->index_player[1]);
	ft_printf("nbr_index[2]: %i\n", all->index_player[2]);
	ft_printf("nbr_index[3]: %i\n", all->index_player[3]);
	while (tmp)
	{
		ft_printf("index_champ: %i\n", tmp->index);
		ft_printf("champ_magic: %.8x\n", tmp->champ->magic);
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
}

int				main(int ac, char **av)
{
	t_vm	*all;

	all = parce_argv(ac, av);
	ft_memset(all->map, '0', MEM_SIZE * 2);
	vm_map(all, all->champs);
	test(all);
	// vm_map(1, champ->prog, champ->prog_size);
	return (0);
}
