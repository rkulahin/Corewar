/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 16:09:17 by rkulahin          #+#    #+#             */
/*   Updated: 2019/03/12 15:03:31 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		win_player(t_players *last)
{
	ft_printf("Contestant %i, \"%s\", has won !\n",
	last->index, last->champ->prog_name);
	system("Leaks virtual_machine");
	exit(1);
}

void		print_and_return(void)
{
	return ;
}

void		replace_map(t_vm *vm, int position, char *ptr, int nb)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (position < 0)
		position = position + 8192;
	while (i < nb)
	{
		vm->map[(position + j) % 8192] = ptr[j];
		i++;
		j++;
	}
}

void		privetstvie(t_vm *vm)
{
	t_players	*tmp;
	int			i;

	i = 0;
	ft_printf("Introducing contestants...\n");
	while (++i != 5)
	{
		tmp = vm->players;
		while (tmp)
		{
			if (tmp->index == i)
			{
				ft_printf("* Player %i, weighing %i bytes, \"%s\" (\"%s\") !\n",
				i, tmp->champ->prog_size, tmp->champ->prog_name,
				tmp->champ->comment);
				break ;
			}
			tmp = tmp->next;
		}
	}
}
