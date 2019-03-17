/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 11:46:53 by seshevch          #+#    #+#             */
/*   Updated: 2019/03/15 17:10:09 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int				find_cycle(int nbr)
{
	if (nbr > 0 && nbr < 16)
		return (g_optab[nbr - 1].num_cycle);
	return (0);
}

t_carriage		*init_carriage(t_vm *vm, int index, int position)
{
	t_carriage	*new;

	new = (t_carriage *)malloc(sizeof(t_carriage));
	new->carry = 0;
	new->live = -1;
	new->index = vm->nbr_car;
	new->nbr_plr = index;
	new->position = position;
	new->next = NULL;
	new->operation[0] = vm->map[position];
	new->operation[1] = vm->map[position + 1];
	new->cycle = find_cycle(vm_atoi_16(new->operation)) + vm->cycle;
	ft_bzero(new->regist, sizeof(int) * 16);
	new->regist[0] = 0 - index;
	vm->nbr_car += 1;
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
	if (new->regist[0] < tmp->regist[0])
	{
		new->next = tmp;
		vm->carriage = new;
		return ;
	}
	while (tmp->next)
	{
		if (new->regist[0] < tmp->next->regist[0])
		{
			new->next = tmp->next;
			tmp->next = new;
			return ;
		}
		tmp = tmp->next;
	}
	tmp->next = new;
}

void			check_lost_byte(int i, char *str, t_players *plr, t_vm *vm)
{
	int					k;
	unsigned int		z;

	k = -1;
	z = 0;
	while (str[++k] && z < (plr->champ->prog_size % 4) * 2)
	{
		vm->color[i] = plr->index + 1;
		vm->map[i] = str[k];
		z++;
		i++;
	}
}

void			vm_map(t_vm *vm, t_players *plr, int i, int k)
{
	unsigned int	j;
	int				byt;
	char			*str;
	t_carriage		*new;

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
				vm->color[i] = plr->index + 1;
				vm->map[i] = str[k];
				i++;
			}
			free(str);
			j++;
		}
		if (plr->champ->prog_size % 4)
			check_lost_byte(i, vm_itoa_16(plr->champ->prog[j]), plr, vm);
		new = init_carriage(vm, plr->index, (plr->index - 1) * byt);
		add_carriage(vm, new);
		plr = plr->next;
	}
}
