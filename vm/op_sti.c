/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 15:53:02 by rkulahin          #+#    #+#             */
/*   Updated: 2019/02/23 16:50:29 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int		find_ind(t_vm *vm, char *str)
{
	int		t_ind;
	int		nb;

	nb = (short)vm_atoi_16(str);
	t_ind = vm_atoi_16(valid_str(vm, (nb % IDX_MOD) * 2, 8));
	return (t_ind);
}

static int		*save_arg(t_vm *vm, t_carriage *cr, int *args)
{
	int		*t_args;

	t_args = (int *)malloc(sizeof(int) * 3);
	t_args[0] = 0;
	if (args[1] == T_IND)
		t_args[1] = find_ind(vm, valid_str(vm, cr->position +
		4, 4));
	if (args[1] == T_REG)
		t_args[1] = (unsigned char)vm_atoi_16(valid_str(vm, cr->position +
	2, 2));
	if (args[1] == T_DIR)
		t_args[1] = (short)vm_atoi_16(valid_str(vm, cr->position + 4, 4));
	if (args[2] == T_REG)
		t_args[2] = (unsigned char)find_ind(vm,
		valid_str(vm, cr->position + 6, 2));
	else
		t_args[2] = (short)find_ind(vm,
		valid_str(vm, cr->position + 6, 4));
	return (t_args);
}

static void		print_sti(int *t_args, t_carriage *cr)
{
	ft_printf("P%5i | sti r%i %i %i\n", cr->index,
	t_args[0], t_args[1], t_args[2]);
	ft_printf("      | -> store to %i + %i = %i (with pc and mod %i)\n",
	t_args[1], t_args[2], t_args[1] + t_args[2],
	(cr->position / 2) + ((t_args[1] + t_args[2]) % IDX_MOD));
}

void			op_sti(t_vm *vm, t_carriage *cr)
{
	char	*str_cotage;
	char	*reg;
	int		*args;
	int		*t_args;
	int		dist;

	dist = -1;
	str_cotage = valid_str(vm, cr->position, 2);
	args = check_arg(vm_atoi_16(str_cotage));
	if (args[0] == T_REG && args[2] != T_IND)
	{
		reg = valid_str(vm, cr->position + 2, 2);
		t_args = save_arg(vm, cr, args);
		replace_map(vm, cr->position + ((t_args[1] + t_args[2]) % IDX_MOD) * 2,
		reg, 2);
		if ((vm->nbr_log & 4) == 4)
			print_sti(t_args, cr);
	}
	while (++dist < 3)
	{
		if (args[dist] == T_REG)
			cr->position = cr->position + 2;
		if (args[dist] == T_DIR || args[dist] == T_IND)
			cr->position = cr->position + 4;
	}
}
