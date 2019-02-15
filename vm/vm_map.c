/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 11:46:53 by seshevch          #+#    #+#             */
/*   Updated: 2019/02/15 18:00:43 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int				find_cycle(char c1, char c2)
{
	if (c1 == '1' && c2 == '0')
		return (2);
	else if (c1 == '0' && (c2 == '2' || c2 == '3'))
		return (5);
	else if (c1 == '0' && (c2 == '6' || c2 == '7' || c2 == '8'))
		return (6);
	else if (c1 == '0' && (c2 == '1' || c2 == '4' || c2 == '5' || c2 == 'd'))
		return (10);
	else if (c1 == '0' && c2 == '9')
		return (20);
	else if (c1 == '0' && (c2 == 'a' || c2 == 'b'))
		return (25);
	else if (c1 == '0' && c2 == 'e')
		return (50);
	else if (c1 == '0' && c2 == 'c')
		return (800);
	else if (c1 == '0' && c2 == 'f')
		return (1000);
	return (0);
}

t_carriage		*init_carriage(t_vm *vm, int index, int position)
{
	t_carriage	*new;

	new = (t_carriage *)malloc(sizeof(t_carriage));
	new->carry = 0;
	new->live = 0;
	new->nbr_plr = index;
	new->position = position;
	new->next = NULL;
	new->operation[0] = vm->map[position];
	new->operation[1] = vm->map[position + 1];
	new->cycle = find_cycle(vm->map[position], vm->map[position + 1]);
	ft_bzero(new->regist, 128);
	new->regist[0] = 0 - index;
	return (new);
}

void			add_carriage(t_vm *vm, t_carriage *new)
{
	t_carriage	*tmp;

	tmp = vm->carriage;
	if (!vm->carriage)
	{
		vm->carriage = new;
		return ;
	}
	if (new->regist[0] > tmp->regist[0] && !tmp->next)
	{
		new->next = tmp;
		vm->carriage = new;
		return ;
	}
	while (tmp->next)
	{
		if (new->regist[0] > tmp->next->regist[0])
		{
			new->next = tmp->next;
			tmp->next = new;
			return ;
		}
		tmp = tmp->next;
	}
	tmp->next = new;
}

void			vm_map(t_vm *vm, t_players *plr, int i, int k)
{
	unsigned int	j;
	int				byt;
	char			*str;

	byt = MEM_SIZE * 2 / vm->nbr_plrs;
	while (plr)
	{
		i = (plr->index - 1) * byt;
		j = 0;
		while (j < plr->champ->prog_size / 4)
		{
			k = -1;
			str = vm_itoa_16(plr->champ->prog[j]);
			while (str[++k])
			{
				vm->map[i] = str[k];
				i++;
			}
			free(str);
			j++;
		}
		add_carriage(vm, init_carriage(vm, plr->index, (plr->index - 1) * byt));
		plr = plr->next;
	}
}
