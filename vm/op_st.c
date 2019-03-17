/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 14:36:08 by rkulahin          #+#    #+#             */
/*   Updated: 2019/03/17 17:25:27 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

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
	while (++i < 2)
		if (args[i] == T_IND)
			t_args[i] = arg_find(vm, cr, 4, j);
		else if (args[i] == T_REG)
			t_args[i] = arg_find(vm, cr, 2, j);
		else if (args[i] == T_DIR)
			t_args[i] = arg_find(vm, cr, 8, j);
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

static void		helper(t_vm *vm, t_carriage *cr, int *args_type, int *arg_n)
{
	char	*s;

	if (check(cr, &arg_n, args_type))
	{
		if (args_type[1] == T_IND)
		{
			s = vm_itoa_16(cr->regist[arg_n[0] - 1]);
			replace_map(vm, (cr->position + (arg_n[1] % IDX_MOD) * 2) %
			8192, s, 8);
			free(s);
			recolor_map(vm, (cr->position + (arg_n[1] % IDX_MOD) * 2) %
			8192, 8, cr->nbr_plr + 1);
		}
		if ((vm->nbr_log & 4) == 4)
			ft_printf("P %4i | st r%i %i\n", cr->index, arg_n[0], arg_n[1]);
	}
}

void			op_st(t_vm *vm, t_carriage *cr)
{
	int		*args_type;
	int		*arg_n;
	int		new_position;
	char	*s;

	new_position = 0;
	s = valid_str(vm, cr->position, 2);
	args_type = check_arg(vm_atoi_16(s));
	free(s);
	arg_n = save_arg(vm, cr, args_type, &new_position);
	helper(vm, cr, args_type, arg_n);
	free(args_type);
	free(arg_n);
	cr->position += new_position + 4;
}
