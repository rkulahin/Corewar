/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 14:39:34 by rkulahin          #+#    #+#             */
/*   Updated: 2019/02/21 14:51:48 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		op_aff(t_vm *vm, t_carriage *cr)
{
	char	*str_cotage;
	int		*args;

	str_cotage = valid_str(vm, cr->position, 2);
	args = check_arg(vm_atoi_16(str_cotage));
	if (args[0] == T_REG)
	{
		ft_printf("%c", (unsigned char)vm_atoi_16(valid_str(vm, cr->position +
		2, 2)));
	}
	if (args[0] == T_IND || args[0] == T_REG)
		cr->position = cr->position + 6;
	else
		cr->position = cr->position + 8;
}
