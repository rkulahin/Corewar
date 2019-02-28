/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_load.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 13:11:41 by seshevch          #+#    #+#             */
/*   Updated: 2019/02/28 13:46:22 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int		convert_ind(t_vm *vm, t_carriage *car, char *str)
{
	int			numb;

	numb = vm_atoi_16(valid_str(vm,
	(car->position - 2 + ((vm_atoi_16(str) % IDX_MOD) * 2)) % 8192, 8));
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

void			op_load(t_vm *vm, t_carriage *cr)
{
	int				*arg;
	char			*str;
	unsigned char	reg;

	arg = check_arg(vm_atoi_16(valid_str(vm, cr->position, 2)));
	if (arg[0] == T_DIR && arg[1] == T_REG)
	{
		str = valid_str(vm, (cr->position + 2) % 8192, 10);
		reg = (unsigned char)vm_atoi_16(str + 8);
		str[8] = '\0';
		if (reg <= 0 || reg > 16)
		{
			push_position(arg, cr);
			return ;
		}
		cr->regist[reg - 1] = (unsigned int)vm_atoi_16(str);
		cr->carry = cr->regist[reg - 1] == 0 ? 1 : 0;
		if ((vm->nbr_log & 4) == 4)
			ft_printf("P%5d | ld %d r%d\n", cr->index, cr->regist[reg - 1], reg);
	}
	else if (arg[0] == T_IND && arg[1] == T_REG)
	{
		str = valid_str(vm, (cr->position + 2) % 8192, 6);
		reg = (unsigned char)vm_atoi_16(str + 4);
		str[4] = '\0';
		if (reg <= 0 || reg > 16)
		{
			push_position(arg, cr);
			return ;
		}
		cr->regist[reg - 1] = (unsigned int)convert_ind(vm, cr, str);
		cr->carry = cr->regist[reg - 1] == 0 ? 1 : 0;
		if ((vm->nbr_log & 4) == 4)
			ft_printf("P%5d | ld %d r%d\n", cr->index, cr->regist[reg - 1], reg);
	}
	push_position(arg, cr);
}
