/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 18:21:46 by rkulahin          #+#    #+#             */
/*   Updated: 2019/02/19 19:19:32 by rkulahin         ###   ########.fr       */
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

t_carriage	*copy_carriage(t_carriage *cr)
{
	t_carriage	*new;

	new = (t_carriage *)malloc(sizeof(t_carriage));
	new->carry = cr->carry;
	new->cycle = 0;
	new->live = cr->live;
	new->nbr_plr = cr->nbr_plr;
	copy_regist(new, cr);
	new->next = NULL;
	return (new);
}

void		op_fork(t_vm *vm, t_carriage *cr)
{
	t_carriage	*new;
	int			dir;

	dir = (short)vm_atoi_16(valid_str(vm, cr->position, 4));
	new = copy_carriage(cr);
	new->position = (((dir % IDX_MOD) * 2) + cr->position) % 8192;
	new->operation[0] = vm->map[new->position];
	if (new->position == 8191)
		new->operation[1] = vm->map[0];
	else
		new->operation[1] = vm->map[new->position + 1];
	cr->position = (cr->position + T_DIR * 2) % 8192;
	run_to_command(vm, new);
	add_carriage(vm, new);
}

void		op_lfork(t_vm *vm, t_carriage *cr)
{
	t_carriage	*new;
	int			dir;

	dir = (short)vm_atoi_16(valid_str(vm, cr->position, 4));
	new = copy_carriage(cr);
	new->position = ((dir * 2) + cr->position) % 8192;
	new->operation[0] = vm->map[new->position];
	if (new->position == 8191)
		new->operation[1] = vm->map[0];
	else
		new->operation[1] = vm->map[new->position + 1];
	cr->position = (cr->position + T_DIR * 2) % 8192;
	run_to_command(vm, new);
	add_carriage(vm, new);
}
