/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_long_load.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seshevch <seshevch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 17:43:31 by seshevch          #+#    #+#             */
/*   Updated: 2019/02/21 17:53:50 by seshevch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int		convert_ind(t_vm *vm, t_carriage *car, char *str)
{
	int			numb;

	numb = vm_atoi_16(valid_str(vm,
	(car->position - 2 + (vm_atoi_16(str) * 2)) % 8192, 4));
	return (numb);
}

static void		push_position(int *arg, t_carriage *car)
{
	int			i;

	i = -1;
	car->position = (car->position + 4) % 8192;
	while (++i < 2)
	{
		if (arg[i] == T_REG)
			car->position = (car->position + 2) % 8192;
		else if (arg[i] == T_IND)
			car->position = (car->position + 4) % 8192;
		else if (arg[i] == T_DIR)
			car->position = (car->position + 8) % 8192;
	}
}

void			op_long_load(t_vm *vm, t_carriage *car)
{
	int				*arg;
	char			*str;
	unsigned char	reg;

	arg = check_arg(vm_atoi_16(valid_str(vm, car->position, 2)));
	if (arg[0] == T_DIR && arg[1] == T_REG)
	{
		str = valid_str(vm, (car->position + 2) % 8192, 10);
		reg = (unsigned char)vm_atoi_16(str + 8);
		str[8] = '\0';
		car->regist[reg] = (unsigned int)vm_atoi_16(str);
		car->carry = car->regist[reg] == 0 ? 1 : 0;
	}
	else if (arg[0] == T_IND && arg[1] == T_REG)
	{
		str = valid_str(vm, (car->position + 2) % 8192, 6);
		reg = (unsigned char)vm_atoi_16(str + 4);
		str[4] = '\0';
		car->regist[reg] = (unsigned int)convert_ind(vm, car, str);
		car->carry = car->regist[reg] == 0 ? 1 : 0;
	}
	push_position(arg, car);
}
