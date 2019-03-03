/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 15:30:47 by seshevch          #+#    #+#             */
/*   Updated: 2019/03/03 16:55:46 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int		*save_arg(t_vm *vm, t_carriage *cr, int *args, int *j)
{
	int		*t_args;
	int		i;

	t_args = (int *)malloc(sizeof(int) * 3);
	i = -1;
	while (++i < 3)
		if (args[i] == T_IND)
		{
			t_args[i] = (short)vm_atoi_16(valid_str(vm, cr->position +
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
			t_args[i] = (unsigned int)vm_atoi_16(valid_str(vm, cr->position +
			2 + *j, 8));
			*j += 8;
		}
	return (t_args);
}

static int		check(int **args_number, int *args_type)
{
	int		j;
	int		i;

	i = -1;
	j = 1;
	if (args_type[0] != T_REG || args_type[1] != T_REG || args_type[2] != T_REG)
		j = 0;
	while (++i < 3)
	{
		if (args_type[i] == T_REG && args_number[0][i] > 0 &&
		args_number[0][i] < 17)
			args_number[0][i] = args_number[0][i];
		else if (args_type[i] == T_REG)
			j = 0;
	}
	return (j);
}

void			op_add(t_vm *vm, t_carriage *cr)
{
	int				*args_type;
	int				*args_number;
	int				new_position;

	new_position = 0;
	args_type = check_arg(vm_atoi_16(valid_str(vm, cr->position, 2)));
	args_number = save_arg(vm, cr, args_type, &new_position);
	if (check(&args_number, args_type))
	{
		cr->regist[args_number[2] - 1] = cr->regist[args_number[0] - 1] +
		cr->regist[args_number[1] - 1];
		cr->carry = cr->regist[args_number[2] - 1] == 0 ? 1 : 0;
		if ((vm->nbr_log & 4) == 4)
			ft_printf("P%5d | add r%d r%d r%d\n", cr->index,
			args_number[0], args_number[1], args_number[2]);
	}
	cr->position += new_position + 4;
}
