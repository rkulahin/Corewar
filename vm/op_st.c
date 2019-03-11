/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seshevch <seshevch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 14:36:08 by rkulahin          #+#    #+#             */
/*   Updated: 2019/03/09 14:54:02 by seshevch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int		*save_arg(t_vm *vm, t_carriage *cr, int *args, int *j)
{
	int		*t_args;
	int		i;

	t_args = (int *)malloc(sizeof(int) * 3);
	i = -1;
	while (++i < 2)
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

static int		check(t_carriage *cr, int **args_number, int *args_type)
{
	int	j;

	j = 1;
	if (args_type[0] != T_REG || args_type[1] == T_DIR ||
	args_number[0][0] <= 0 || args_number[0][0] >= 17 || args_type[1] == 0)
		j = 0;
	else if ((args_type[1] == T_REG) && (args_number[0][1] <= 0 ||
	args_number[0][1] >= 17))
		j = 0;
	else if (args_type[1] == T_REG && args_number[0][1] > 0 &&
	args_number[0][1] < 17)
		cr->regist[args_number[0][1] - 1] =
		cr->regist[args_number[0][0] - 1];
	return (j);
}



void			op_st(t_vm *vm, t_carriage *cr)
{
	int		*args_type;
	int		*args_number;
	int		new_position;

	new_position = 0;
	args_type = check_arg(vm_atoi_16(valid_str(vm, cr->position, 2)));
	args_number = save_arg(vm, cr, args_type, &new_position);
	if (check(cr, &args_number, args_type))
	{
		if (args_type[1] == T_IND)
			replace_map(vm, (cr->position + (args_number[1] % IDX_MOD) * 2) %
			8192, vm_itoa_16(cr->regist[args_number[0] - 1]), 8);
		if ((vm->nbr_log & 4) == 4)
			ft_printf("P %4i | st r%i %i\n", cr->index, args_number[0],
			args_number[1]);
	}
	cr->position += new_position + 4;
}
