/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:28:39 by rkulahin          #+#    #+#             */
/*   Updated: 2019/03/03 17:07:08 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int			find_ind(t_vm *vm, int pc, char *str)
{
	int		t_ind;
	int		nb;

	nb = (short)vm_atoi_16(str);
	t_ind = (unsigned int)vm_atoi_16(valid_str(vm, pc - 2 + nb, 8));
	return (t_ind);
}

static int			*save_arg(t_vm *vm, t_carriage *cr, int *args, int *j)
{
	int		*t_args;
	int		i;

	t_args = (int *)malloc(sizeof(int) * 3);
	i = -1;
	while (++i < 3)
		if (args[i] == T_IND)
		{
			t_args[i] = find_ind(vm, cr->position, valid_str(vm, cr->position +
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

static int			check(t_carriage *cr, int **args_number, int *args_type)
{
	int		j;
	int		i;

	i = -1;
	j = 1;
	if (args_type[2] != T_REG || args_number[0][0] <= 0 ||
	args_number[0][0] >= 17)
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

void				op_and(t_vm *vm, t_carriage *cr)
{
	int		*args_type;
	int		*args_number;
	int		new_position;

	new_position = 0;
	args_type = check_arg(vm_atoi_16(valid_str(vm, cr->position, 2)));
	args_number = save_arg(vm, cr, args_type, &new_position);
	if (check(cr, &args_number, args_type))
	{
		cr->regist[args_number[2] - 1] = args_number[0] & args_number[1];
		cr->carry = (cr->regist[args_number[2] - 1] == 0 ? 1 : 0);
		if ((vm->nbr_log & 4) == 4)
			ft_printf("P%5i | and %i %i r%i\n",
			cr->index, args_number[0], args_number[1], args_number[2]);
	}
	cr->position += new_position + 4;
}
