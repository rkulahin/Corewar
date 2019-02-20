/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 10:50:31 by rkulahin          #+#    #+#             */
/*   Updated: 2019/02/20 12:28:04 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	op_zjmp(t_vm *vm, t_carriage *cr)
{
	int		zjmp;

	if (cr->carry == 1)
	{
		zjmp = (short)vm_atoi_16(valid_str(vm, cr->position, 4));
		cr->position = ((zjmp % IDX_MOD) * 2) % 8192;
	}
}
