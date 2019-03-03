/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_load_index.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 16:43:49 by seshevch          #+#    #+#             */
/*   Updated: 2019/03/03 15:28:16 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int		find_ind(t_vm *vm, char *str, int position)
{
	int		t_ind;
	int		nb;

	nb = (short)vm_atoi_16(str);
	t_ind = vm_atoi_16(valid_str(vm, (nb % IDX_MOD) * 2 + position - 2, 8));
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
			t_args[i] = (unsigned int)find_ind(vm, valid_str(vm, cr->position +
			2 + *j, 4), cr->position);
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

	i = -1;
	j = 1;
	if (args_type[1] == T_IND || args_type[2] != T_REG ||
		args_number[0][2] <= 0 || args_number[0][2] > 16)
		j = 0;
	while (++i < 2)
	{
		if (args_type[i] == T_REG && args_number[0][i] > 0 &&
		args_number[0][i] < 17)
			args_number[0][i] = cr->regist[args_number[0][i] - 1];
		else if (args_type[i] == T_REG)
			j = 0;
	}
	return (j);
}

static void			print_v4(t_carriage *cr, int *ar)
{
	ft_printf("P%5d | ldi %d %d r%d\n", cr->index, ar[0], ar[1], ar[2]);
	ft_printf("       | -> load from %d + %d = %d (with pc and mod %d)\n",
	ar[0], ar[1], ar[0] + ar[1],
	(((ar[0] + ar[1]) % IDX_MOD) + cr->position / 2) % 4096);
}

void				op_load_index(t_vm *vm, t_carriage *cr)
{
	int				*args_type;
	int				*args_number;
	int				new_position;

	new_position = 0;
	args_type = check_arg(vm_atoi_16(valid_str(vm, cr->position, 2)));
	args_number = save_arg(vm, cr, args_type, &new_position);
	if (check(cr, &args_number, args_type))
	{
		cr->regist[args_number[2] - 1] = (unsigned int)vm_atoi_16(valid_str(vm,
		(((args_number[0] + args_number[1]) % IDX_MOD) * 2 + cr->position - 2)
		% 8192, 8));
		if ((vm->nbr_log & 4) == 4)
			print_v4(cr, args_number);
	}
	cr->position += new_position + 4;
}
