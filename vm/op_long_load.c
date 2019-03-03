/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_long_load.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 17:43:31 by seshevch          #+#    #+#             */
/*   Updated: 2019/03/03 15:29:29 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int		find_ind(t_vm *vm, char *str, int position)
{
	int		t_ind;
	int		nb;

	nb = (short)vm_atoi_16(str);
	t_ind = (short)vm_atoi_16(valid_str(vm, nb * 2 + position - 2, 4));
	return (t_ind);
}

static int		*save_arg(t_vm *vm, t_carriage *cr, int *args, int *j)
{
	int		*t_args;
	int		i;

	t_args = (int *)malloc(sizeof(int) * 3);
	i = -1;
	while (++i < 2)
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

static int		check(int **args_number, int *args_type)
{
	int		j;
	int		i;

	i = -1;
	j = 1;
	if (args_type[0] == T_REG || args_type[1] != T_REG ||
		(args_number[0][1] <= 0 && args_number[0][1] > 16))
		j = 0;
	return (j);
}

void			op_long_load(t_vm *vm, t_carriage *cr)
{
	int				*args_type;
	int				*args_number;
	int				new_position;

	new_position = 0;
	args_type = check_arg(vm_atoi_16(valid_str(vm, cr->position, 2)));
	args_number = save_arg(vm, cr, args_type, &new_position);
	if (check(&args_number, args_type))
	{
		cr->regist[args_number[1] - 1] = args_number[0];
		cr->carry = cr->regist[args_number[1] - 1] == 0 ? 1 : 0;
		if ((vm->nbr_log & 4) == 4)
			ft_printf("P%5d | lld %d r%d\n", cr->index,
			cr->regist[args_number[1] - 1], args_number[1]);
	}
	cr->position += new_position + 4;
}
