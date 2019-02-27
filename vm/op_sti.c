/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seshevch <seshevch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 15:53:02 by rkulahin          #+#    #+#             */
/*   Updated: 2019/02/26 15:29:59 by seshevch         ###   ########.fr       */
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

static int		*save_arg(t_vm *vm, t_carriage *cr, int *args, int j)
{
	int		*t_args;
	int		i;

	t_args = (int *)malloc(sizeof(int) * 3);
	i = -1;
	while (++i < 3)
		if (args[i] == T_IND)
		{
			t_args[i] = find_ind(vm, valid_str(vm, cr->position +
			2 + j, 4));
			j += 4;
		}
		else if (args[i] == T_REG)
		{
			t_args[i] = (unsigned char)vm_atoi_16(valid_str(vm, cr->position +
			2 + j, 2));
			j += 2;
		}
		else if (args[i] == T_DIR)
		{
			t_args[i] = (short)vm_atoi_16(valid_str(vm, cr->position +
			2 + j, 4));
			j += 4;
		}
	return (t_args);
}

static void		print_sti(int *t_args, t_carriage *cr)
{
	ft_printf("P%5i | sti r%i %i %i\n", cr->index,
	t_args[0], t_args[1], t_args[2]);
	ft_printf("       | -> store to %i + %i = %i (with pc and mod %i)\n",
	t_args[1], t_args[2], t_args[1] + t_args[2],
	(cr->position / 2) + ((t_args[1] + t_args[2]) % IDX_MOD));
}

void			op_sti(t_vm *vm, t_carriage *cr)
{
	char	*str_cotage;
	int		reg;
	int		*args;
	int		*t_args;
	int		dist;

	dist = -1;
	str_cotage = valid_str(vm, cr->position, 2);
	args = check_arg(vm_atoi_16(str_cotage));
	if (args[0] == T_REG && args[2] != T_IND)
	{
		reg = (unsigned char)vm_atoi_16(valid_str(vm, cr->position + 2, 2)) - 1;
		t_args = save_arg(vm, cr, args, 0);
		replace_map(vm, cr->position + ((t_args[1] + t_args[2]) % IDX_MOD) * 2,
		vm_itoa_16(cr->regist[reg]), 8);
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
	cr->position += 4;
}
