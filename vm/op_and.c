/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:28:39 by rkulahin          #+#    #+#             */
/*   Updated: 2019/02/20 14:33:01 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			find_ind(t_vm *vm, int pc, char *str)
{
	int		t_ind;
	int		nb;

	nb = (short)vm_atoi_16(str);
	t_ind = vm_atoi_16(valid_str(vm, pc - 2 + nb, 8));
	return (t_ind);
}

static int		*save_arg(int *j, t_vm *vm, t_carriage *cr, int *args)
{
	int		i;
	int		*ar;

	i = -1;
	ar = (int *)malloc(sizeof(int) * 3);
	while (++i < 3)
		if (args[i] == T_REG)
		{
			ar[i] = (unsigned char)vm_atoi_16(valid_str(vm, cr->position +
			2 + *j, 2));
			*j += 2;
		}
		else if (args[i] == T_DIR)
		{
			ar[i] = (int)vm_atoi_16(valid_str(vm, cr->position + 2 + *j, 8));
			*j += 8;
		}
		else if (args[i] == T_IND)
		{
			ar[i] = find_ind(vm, cr->position, (valid_str(vm, cr->position +
			2 + *j, 2)));
			*j += 4;
		}
	return (ar);
}

void			op_and(t_vm *vm, t_carriage *cr)
{
	char	*str_cotage;
	int		*args;
	int		*ar;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str_cotage = valid_str(vm, cr->position, 2);
	args = check_arg(vm_atoi_16(str_cotage));
	if (args[0] != 0 && args[1] != 0 && args[2] == T_REG)
	{
		ar = save_arg(&j, vm, cr, args);
		cr->regist[ar[2]] = ar[0] & ar[1];
		cr->carry = (cr->regist[ar[2]] == 0 ? 1 : 0);
	}
}

void			op_or(t_vm *vm, t_carriage *cr)
{
	char	*str_cotage;
	int		*args;
	int		*ar;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str_cotage = valid_str(vm, cr->position, 2);
	args = check_arg(vm_atoi_16(str_cotage));
	if (args[0] != 0 && args[1] != 0 && args[2] == T_REG)
	{
		ar = save_arg(&j, vm, cr, args);
		cr->regist[ar[2]] = ar[0] | ar[1];
		cr->carry = (cr->regist[ar[2]] == 0 ? 1 : 0);
	}
}

void			op_xor(t_vm *vm, t_carriage *cr)
{
	char	*str_cotage;
	int		*args;
	int		*ar;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str_cotage = valid_str(vm, cr->position, 2);
	args = check_arg(vm_atoi_16(str_cotage));
	if (args[0] != 0 && args[1] != 0 && args[2] == T_REG)
	{
		ar = save_arg(&j, vm, cr, args);
		cr->regist[ar[2]] = ar[0] ^ ar[1];
		cr->carry = (cr->regist[ar[2]] == 0 ? 1 : 0);
	}
}
