/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 14:36:08 by rkulahin          #+#    #+#             */
/*   Updated: 2019/02/20 12:34:39 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		replace_map(t_vm *vm, int positon, char *ptr, int nb)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < nb)
	{
		vm->map[(positon + j) % 8192] = ptr[j];
		i++;
		j++;
	}
}

void		op_st(t_vm *vm, t_carriage *cr)
{
	char	*str_cotage;
	char	*first;
	char	*second;
	int		*args;
	char	*t_ind;

	str_cotage = valid_str(vm, cr->position, 2);
	args = check_arg(vm_atoi_16(str_cotage));
	if (args[0] == T_REG)
	{
		first = valid_str(vm, cr->position + 2, 2);
		second = valid_str(vm, cr->position + 4, 2);
		if (args[1] == T_IND)
		{
			t_ind = valid_str(vm, cr->position - 2 +
			(short)vm_atoi_16(second), 8);
			replace_map(vm, cr->position + (vm_atoi_16(t_ind) %
			IDX_MOD) * 2, first, 2);
			cr->regist[(unsigned char)vm_atoi_16(second)] =
			(unsigned char)vm_atoi_16(first);
		}
	}
	cr->position = cr->position + 4 + (args[0] + args[1]) * 2;
}
