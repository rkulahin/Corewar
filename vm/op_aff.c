/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 14:39:34 by rkulahin          #+#    #+#             */
/*   Updated: 2019/03/11 11:19:43 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

char		*space_byte_print(char *ptr)
{
	char	*str;

	str = ptr;
	return (str);
}

void		op_aff(t_vm *vm, t_carriage *cr)
{
	char	*str_cotage;
	int		*args;
	int		i;

	str_cotage = valid_str(vm, cr->position, 2);
	args = check_arg(vm_atoi_16(str_cotage));
	if (args[0] == T_REG && vm->aff == 1)
	{
		i = vm_atoi_16(valid_str(vm, cr->position + 2, 2));
		if (i > 0 && i < 17)
			ft_printf("Aff: %c\n", cr->regist[i - 1] % 256);
	}
	if (args[0] == T_REG)
		cr->position = cr->position + 6;
	else if (args[0] == T_IND)
		cr->position = cr->position + 8;
	else if (args[0] == T_DIR)
		cr->position = cr->position + 12;
	else
		cr->position += 4;
}
