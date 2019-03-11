/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 15:53:02 by rkulahin          #+#    #+#             */
/*   Updated: 2019/03/11 17:36:08 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int		find_ind(t_vm *vm, int nb)
{
	int		t_ind;
	char	*s;

	s = valid_str(vm, (nb % IDX_MOD) * 2, 8);
	t_ind = vm_atoi_16(s);
	free(s);
	return (t_ind);
}

static int		arg_find(t_vm *vm, t_carriage *cr, int i, int *j)
{
	char	*s;
	int		nb;

	s = NULL;
	s = valid_str(vm, cr->position + 2 + *j, i);
	*j += i;
	if (i == 2)
		nb = (unsigned char)vm_atoi_16(s);
	if (i == 4)
		nb = (short)vm_atoi_16(s);
	if (i == 8)
		nb = (unsigned int)vm_atoi_16(s);
	free(s);
	return (nb);
}

static int		*save_arg(t_vm *vm, t_carriage *cr, int *args, int *j)
{
	int		*t_args;
	int		i;

	i = -1;
	t_args = (int *)malloc(sizeof(int) * 3);
	while (++i < 3)
		if (args[i] == T_IND)
			t_args[i] = find_ind(vm, arg_find(vm, cr, 4, j));
		else if (args[i] == T_REG)
			t_args[i] = arg_find(vm, cr, 2, j);
		else if (args[i] == T_DIR)
			t_args[i] = arg_find(vm, cr, 4, j);
	return (t_args);
}

static int		check(t_carriage *cr, int **args_number, int *args_type)
{
	int		j;
	int		i;

	i = 0;
	j = 1;
	if (args_type[2] == T_IND || args_type[0] != T_REG || args_type[2] == 0 ||
	args_type[1] == 0 || args_number[0][0] <= 0 || args_number[0][0] >= 17)
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

void			op_sti(t_vm *vm, t_carriage *cr)
{
	int		*args_type;
	int		*args_number;
	int		new_position;
	char	*s;

	new_position = 0;
	s = valid_str(vm, cr->position, 2);
	args_type = check_arg(vm_atoi_16(s));
	args_number = save_arg(vm, cr, args_type, &new_position);
	if (check(cr, &args_number, args_type))
	{
		replace_map(vm, cr->position + ((args_number[1] + args_number[2])
		% IDX_MOD) * 2, vm_itoa_16(cr->regist[args_number[0] - 1]), 8);
		if ((vm->nbr_log & 4) == 4)
			print_sti(args_number, cr);
	}
	free(args_type);
	free(args_number);
	free(s);
	cr->position += new_position + 4;
}
