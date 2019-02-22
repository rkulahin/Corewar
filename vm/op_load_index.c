/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_load_index.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seshevch <seshevch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 16:43:49 by seshevch          #+#    #+#             */
/*   Updated: 2019/02/21 17:53:54 by seshevch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int		*cast_arg_norm(int type[3], char *str)
{
	int			arg[3];

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
	int			arg[3];

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

void			op_load_index(t_vm *vm, t_carriage *cr)
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
		cr->regist[arg[2]] = (unsigned int)vm_atoi_16(valid_str(vm,
		(((arg[0] + arg[1]) % IDX_MOD) * 2 + cr->position - 2) % 8192, 8));
	}
	else if (tp[0] == 4 && (tp[1] == 1 || tp[1] == 2) && tp[2] == 1)
	{
		str = valid_str(vm, (cr->position + 2) % 8192,
				(2 + tp[1] + tp[2]) * 2);
		arg = cast_arg_ind(vm, tp, str, cr->position);
		cr->regist[arg[2]] = (unsigned int)vm_atoi_16(valid_str(vm,
		(((arg[0] + arg[1]) % IDX_MOD) * 2 + cr->position - 2) % 8192, 8));
	}
	push_position(tp, cr);
}
