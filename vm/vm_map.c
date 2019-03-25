/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seshevch <seshevch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 11:46:53 by seshevch          #+#    #+#             */
/*   Updated: 2019/03/22 14:48:35 by seshevch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			init_carriage(t_vm *vm, int index, int position)
{
	t_carriage	*new;
	int			nbr;

	new = (t_carriage *)malloc(sizeof(t_carriage));
	new->carry = 0;
	new->live = -1;
	new->index = vm->nbr_car;
	new->nbr_plr = index;
	new->position = position;
	new->next = NULL;
	new->prev = NULL;
	new->operation[0] = vm->map[position];
	new->operation[1] = vm->map[position + 1];
	nbr = vm_atoi_16(new->operation);
	if (nbr > 0 && nbr < 16)
		new->cycle = g_optab[nbr - 1].num_cycle + vm->cycle;
	else
		new->cycle = 0 + vm->cycle;
	ft_bzero(new->regist, sizeof(int) * 16);
	new->regist[0] = 0 - index;
	vm->nbr_car += 1;
	add_carriage(vm, new);
}

static void		helper(t_vm *vm, t_carriage *tmp, t_carriage *new)
{
	new->next = tmp;
	tmp->prev = new;
	vm->carriage = new;
}

void			add_carriage(t_vm *vm, t_carriage *new)
{
	t_carriage	*tmp;

	tmp = vm->carriage;
	if (!vm->carriage)
		vm->carriage = new;
	else if (new->regist[0] < tmp->regist[0])
		helper(vm, tmp, new);
	else
	{
		while (tmp->next)
		{
			if (new->regist[0] < tmp->next->regist[0])
			{
				new->next = tmp->next;
				tmp->next->prev = new;
				tmp->next = new;
				new->prev = tmp;
				return ;
			}
			tmp = tmp->next;
		}
		new->prev = tmp;
		tmp->next = new;
	}
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
	free(str);
}

void			vm_map(t_vm *vm, t_players *plr, int i, int k)
{
	int				j;
	int				byt;
	char			*str;

	byt = MEM_SIZE * 2 / vm->nbr_plrs;
	while (plr && (j = -1) == -1)
	{
		i = (plr->index - 1) * byt;
		while (++j < (int)(plr->champ->prog_size / 4) && (k = -1) == -1)
		{
			str = vm_itoa_16(plr->champ->prog[j]);
			while (str[++k])
			{
				vm->color[i] = plr->index + 1;
				vm->map[i] = str[k];
				i++;
			}
			free(str);
		}
		if (plr->champ->prog_size % 4)
			check_lost_byte(i, vm_itoa_16(plr->champ->prog[j]), plr, vm);
		init_carriage(vm, plr->index, (plr->index - 1) * byt);
		plr = plr->next;
	}
}
