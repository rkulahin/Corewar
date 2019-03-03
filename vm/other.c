/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 16:09:17 by rkulahin          #+#    #+#             */
/*   Updated: 2019/03/03 18:19:46 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		win_player(t_players *last)
{
	ft_printf("Contestant %i, \"%s\", has won !\n",
	last->index, last->champ->prog_name);
	exit(1);
}

void		print_and_return(void)
{
	return ;
}

void		run_to_command(t_vm *vm, t_carriage *cr, int j)
{
	int		check;
	int		i;

	check = 1;
	if (cr->position < 0)
		cr->position += 8192;
	while (check)
	{
		cr->position = cr->position % 8192;
		cr->operation[0] = vm->map[cr->position];
		cr->operation[1] = vm->map[(cr->position + 1) % 8192];
		i = (unsigned char)vm_atoi_16(cr->operation);
		if ((i >= 1 && i <= 16) || check == 2 || j == 1)
			break ;
		else
			check = 2;
		cr->position += 2;
	}
	if (i >= 1 && i <= 16)
		cr->cycle = g_optab[i - 1].num_cycle + vm->cycle;
	else
		cr->cycle = vm->cycle;
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
