/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 15:53:02 by rkulahin          #+#    #+#             */
/*   Updated: 2019/03/03 13:57:04 by rkulahin         ###   ########.fr       */
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

static int		*save_arg(t_vm *vm, t_carriage *cr, int *args, int *j)
{
	int		*t_args;
	int		i;

	t_args = (int *)malloc(sizeof(int) * 3);
	i = -1;
	while (++i < 3)
		if (args[i] == T_IND)
		{
			t_args[i] = find_ind(vm, valid_str(vm, cr->position +
			2 + *j, 4));
			*j += 4;
		}
		else if (args[i] == T_REG)
		{
			t_args[i] = (unsigned char)vm_atoi_16(valid_str(vm, cr->position +
			2 + *j, 2));
			*j += 2;
		}
		else if (args[i] == T_DIR)
		{
			t_args[i] = (short)vm_atoi_16(valid_str(vm, cr->position +
			2 + *j, 4));
			*j += 4;
		}
	return (t_args);
}

static int		check(t_carriage *cr, int **args_number, int *args_type)
{
	int		j;
	int		i;

	i = 0;
	j = 1;
	if (args_type[2] == T_IND || args_type[0] != T_REG ||
	args_number[0][0] <= 0 || args_number[0][0] >= 17)
		j = 0;
	while (++i < 3)
	{
		if (args_type[i] == T_REG && args_number[0][i] > 0 &&
		args_number[0][i] < 17)
			args_number[0][i] = cr->regist[args_number[0][i] - 1];
		else if (args_type[i] == T_REG)
			j = 0;
	}
	return (j);
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
	int		*args_type;
	int		*args_number;
	int		new_position;

	new_position = 0;
	args_type = check_arg(vm_atoi_16(valid_str(vm, cr->position, 2)));
	args_number = save_arg(vm, cr, args_type, &new_position);
	if (check(cr, &args_number, args_type))
	{
		replace_map(vm, cr->position + ((args_number[1] + args_number[2])
		% IDX_MOD) * 2, vm_itoa_16(cr->regist[args_number[0] - 1]), 8);
		if ((vm->nbr_log & 4) == 4)
			print_sti(args_number, cr);
	}
	cr->position += new_position + 4;
}
