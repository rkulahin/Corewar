/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_load_index.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 16:43:49 by seshevch          #+#    #+#             */
/*   Updated: 2019/03/03 11:53:31 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int		*cast_arg_norm(int type[3], char *str)
{
	int			*arg;

	arg = (int *)malloc(sizeof(int) * 3);
	arg[2] = (unsigned char)vm_atoi_16(str + ((type[0] + type[1]) * 2));
	str[(type[0] + type[1]) * 2] = '\0';
	if (type[1] == 1)
		arg[1] = (unsigned char)vm_atoi_16(str + (type[0] * 2));
	else
		arg[1] = (short)vm_atoi_16(str + (type[0] * 2));
	str[type[0] * 2] = '\0';
	if (type[0] == 1)
		arg[0] = (unsigned char)vm_atoi_16(str);
	else
		arg[0] = (short)vm_atoi_16(str);
	return (arg);
}

static int		*cast_arg_ind(t_vm *vm, int type[3], char *str, int position)
{
	int			*arg;

	arg = (int *)malloc(sizeof(int) * 3);
	arg[2] = (unsigned char)vm_atoi_16(str + ((2 + type[1]) * 2));
	str[(2 + type[1]) * 2] = '\0';
	if (type[1] == 1)
		arg[1] = (unsigned char)vm_atoi_16(str + 4);
	else
		arg[1] = (short)vm_atoi_16(str + 4);
	str[4] = '\0';
	arg[0] = (unsigned int)valid_str(vm, ((vm_atoi_16(str) % IDX_MOD) * 2 +
											position - 2) % 8192, 8);
	return (arg);
}

static void		push_position(int *tp, t_carriage *car)
{
	int			i;

	i = -1;
	car->position = (car->position + 4) % 8192;
	while (++i < 3)
	{
		if (tp[i] == T_REG)
			car->position = (car->position + 2) % 8192;
		else if (tp[i] == T_IND || tp[i] == T_DIR)
			car->position = (car->position + 4) % 8192;
	}
}

static void			print_op(int *arg, t_carriage *cr, t_vm *vm)
{
	if ((vm->nbr_log & 4) == 4)
	{
		ft_printf("P%5d | ldi %d %d r%d\n", cr->index, arg[0], arg[1], arg[2]);
		ft_printf("       | -> load from %d + %d = %d (with pc and mod %d)\n",
					arg[0], arg[1], arg[0] + arg[1],
					(((arg[0] + arg[1]) % IDX_MOD) + cr->position / 2) % 4096);
	}
}

static int			check_ar(int **ar, int *args)
{
	int		i;
	int		j;

	j = 1;
	i = 0;
	while (++i < 2)
	{
		if (ar[0][i] == 1)
			ar[0][i] = -1;
		else if (ar[0][i] > 1 && ar[0][i] < 17 && args[i] != T_REG)
			ar[0][i] = 0;
		else if (ar[0][i] > 1 && ar[0][i] < 17)
			ar[0][i] = ar[0][i];
		else if (args[i] == T_REG && 
		else
			j = 0;
	}
	if (ar[0][2] <= 0 || ar[0][2] >= 17)
		j = 0;
	return (j);
}

static void			replace_ar(int **ar, int *args, t_carriage *cr)
{
	int		i;

	i = -1;
	while (++i < 2)
		if (args[i] == T_REG)
			ar[0][i] = cr->regist[ar[0][i] - 1];
}

static void			check(t_vm *vm, t_carriage *cr, int *arg, int *tp)
{
	if (check_ar(&arg, tp))
	{
		replace_ar(&arg, tp, cr);
		cr->regist[arg[2] - 1] = (unsigned int)vm_atoi_16(valid_str(vm,
		(((arg[0] + arg[1]) % IDX_MOD) * 2 + cr->position - 2) % 8192, 8));
		print_op(arg, cr, vm);
	}
}

void				op_load_index(t_vm *vm, t_carriage *cr)
{
	int				*tp;
	int				*arg;
	char			*str;

	tp = check_arg(vm_atoi_16(valid_str(vm, cr->position, 2)));
	if ((tp[0] == 1 || tp[0] == 2) && (tp[1] == 1 || tp[1] == 2) && tp[2] == 1)
	{
		str = valid_str(vm, (cr->position + 2) % 8192,
				(tp[0] + tp[1] + tp[2]) * 2);
		arg = cast_arg_norm(tp, str);
		check(vm, cr, arg, tp);
	}
	else if (tp[0] == 4 && (tp[1] == 1 || tp[1] == 2) && tp[2] == 1)
	{
		str = valid_str(vm, (cr->position + 2) % 8192,
				(2 + tp[1] + tp[2]) * 2);
		arg = cast_arg_ind(vm, tp, str, cr->position);
		check(vm, cr, arg, tp);
	}
	push_position(tp, cr);
}
