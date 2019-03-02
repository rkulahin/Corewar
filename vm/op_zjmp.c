/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 10:50:31 by rkulahin          #+#    #+#             */
/*   Updated: 2019/03/02 11:50:52 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	op_zjmp(t_vm *vm, t_carriage *cr)
{
	int		zjmp;

	zjmp = (short)vm_atoi_16(valid_str(vm, cr->position, 4));
	if (cr->carry == 1)
	{
		cr->position += ((zjmp % IDX_MOD) * 2) % 8192;
	}
	else
		cr->position += 6;
	if ((vm->nbr_log & 4) == 4)
	{
		if (cr->carry == 1)
			ft_printf("P%5i | zjmp %i OK\n", cr->index, zjmp);
		else
			ft_printf("P%5i | zjmp %i FAILED\n", cr->index, zjmp);
	}
}
