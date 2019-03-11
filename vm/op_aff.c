/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 14:39:34 by rkulahin          #+#    #+#             */
/*   Updated: 2019/03/11 17:40:08 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		op_aff(t_vm *vm, t_carriage *cr)
{
	char	*str_cotage;
	int		*args;
	char	*str;
	int		i;

	str_cotage = valid_str(vm, cr->position, 2);
	args = check_arg(vm_atoi_16(str_cotage));
	if (args[0] == T_REG && vm->aff == 1)
	{
		str = valid_str(vm, cr->position + 2, 2);
		i = vm_atoi_16(str);
		if (i > 0 && i < 17)
			ft_printf("Aff: %c\n", cr->regist[i - 1] % 256);
		free(str);
	}
	if (args[0] == T_REG)
		cr->position = cr->position + 6;
	else if (args[0] == T_IND)
		cr->position = cr->position + 8;
	else if (args[0] == T_DIR)
		cr->position = cr->position + 12;
	else
		cr->position += 4;
	free(str_cotage);
	free(args);
}
