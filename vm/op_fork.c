/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 18:21:46 by rkulahin          #+#    #+#             */
/*   Updated: 2019/03/17 15:52:26 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		copy_regist(t_carriage *new, t_carriage *cr)
{
	int		i;

	i = 0;
	while (i < REG_NUMBER)
	{
		new->regist[i] = cr->regist[i];
		i++;
	}
}

t_carriage	*copy_carriage(t_vm *vm, t_carriage *cr)
{
	t_carriage	*new;

	new = (t_carriage *)malloc(sizeof(t_carriage));
	new->carry = cr->carry;
	new->cycle = -1;
	new->index = vm->nbr_car;
	new->live = cr->live;
	new->nbr_plr = cr->nbr_plr;
	copy_regist(new, cr);
	new->next = NULL;
	new->prev = NULL;
	vm->nbr_car = vm->nbr_car + 1;
	return (new);
}

void		op_fork(t_vm *vm, t_carriage *cr)
{
	t_carriage	*new;
	int			dir;
	char		*s;

	s = valid_str(vm, cr->position, 4);
	dir = (short)vm_atoi_16(s);
	new = copy_carriage(vm, cr);
	new->position = (((dir % IDX_MOD) * 2) + cr->position) % 8192;
	if (new->position < 0)
		new->position += 8192;
	if ((vm->nbr_log & 4) == 4)
		ft_printf("P %4i | fork %i (%i)\n", cr->index, dir,
	((dir % IDX_MOD) + cr->position / 2) % 4096);
	cr->position = cr->position + 6;
	new->next = vm->carriage;
	vm->carriage->prev = new;
	vm->carriage = new;
	free(s);
}

void		op_lfork(t_vm *vm, t_carriage *cr)
{
	t_carriage	*new;
	int			dir;
	char		*s;

	s = valid_str(vm, cr->position, 4);
	dir = (short)vm_atoi_16(s);
	new = copy_carriage(vm, cr);
	new->position = ((dir * 2) + cr->position) % 8192;
	if (new->position < 0)
		new->position += 8192;
	if ((vm->nbr_log & 4) == 4)
		ft_printf("P %4i | lfork %i (%i)\n", cr->index, dir,
	(dir + cr->position / 2));
	cr->position = cr->position + 6;
	new->next = vm->carriage;
	vm->carriage->prev = new;
	vm->carriage = new;
	free(s);
}
