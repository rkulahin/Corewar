/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_add_sub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seshevch <seshevch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 19:20:29 by seshevch          #+#    #+#             */
/*   Updated: 2019/02/23 12:56:20 by seshevch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

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

void			op_add(t_vm *vm, t_carriage *car)
{
	unsigned int	reg2;
	unsigned int	reg3;
	int				*arg;
	char			*str;

	arg = check_arg(vm_atoi_16(valid_str(vm, car->position, 2)));
	if (arg[0] == T_REG && arg[1] == T_REG && arg[2] == T_REG)
	{
		str = valid_str(vm, (car->position + 2) % 1892, 6);
		reg3 = (unsigned char)vm_atoi_16(str + 4);
		str[4] = '\0';
		reg2 = (unsigned int)vm_atoi_16(str + 2);
		str[2] = '\0';
		car->regist[reg3] = reg2 + (unsigned int)vm_atoi_16(str);
		car->carry = car->regist[reg3] == 0 ? 1 : 0;
		if ((vm->nbr_log & 4) == 4)
			ft_printf("P    %d | add r%d r%d r%d\n", car->index,
			(unsigned int)vm_atoi_16(str), reg2, reg3);
	}
	push_position(arg, car);
}

void			op_sub(t_vm *vm, t_carriage *car)
{
	unsigned int	reg2;
	unsigned int	reg3;
	int				*arg;
	char			*str;

	arg = check_arg(vm_atoi_16(valid_str(vm, car->position, 2)));
	if (arg[0] == T_REG && arg[1] == T_REG && arg[2] == T_REG)
	{
		str = valid_str(vm, (car->position + 2) % 1892, 6);
		reg3 = (unsigned char)vm_atoi_16(str + 4);
		str[4] = '\0';
		reg2 = (unsigned int)vm_atoi_16(str + 2);
		str[2] = '\0';
		car->regist[reg3] = (unsigned int)vm_atoi_16(str) - reg2;
		car->carry = car->regist[reg3] == 0 ? 1 : 0;
		if ((vm->nbr_log & 4) == 4)
			ft_printf("P    %d | sub r%d r%d r%d\n", car->index,
			(unsigned int)vm_atoi_16(str), reg2, reg3);
	}
	push_position(arg, car);
}
