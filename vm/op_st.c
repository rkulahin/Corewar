/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 14:36:08 by rkulahin          #+#    #+#             */
/*   Updated: 2019/02/24 15:41:39 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		print_st(t_carriage *cr, int f, int s, int arg)
{
	if (arg == T_IND)
		ft_printf("P%5i | st r%i %i\n", cr->index, f, s);
	else
		ft_printf("P%5i | st r%i %i\n", cr->index, f, s);
}

static int				perehod(int *args, t_carriage *cr)
{
	int		dist;

	dist = -1;
	while (++dist < 2)
	{
		if (args[dist] == T_REG)
			cr->position = cr->position + 2;
		if (args[dist] == T_IND)
			cr->position = cr->position + 4;
		if (args[dist] == T_DIR)
			cr->position = cr->position + 8;
	}
	return (cr->position + 4);
}

void			op_st(t_vm *vm, t_carriage *cr)
{
	int		*args;
	int		f;
	char	*ff;
	int		s;

	args = check_arg(vm_atoi_16(valid_str(vm, cr->position, 2)));
	ff = valid_str(vm, cr->position + 2, 2);
	f = (unsigned char)vm_atoi_16(ff);
	if (args[0] == T_REG && args[1] == T_IND)
	{
		s = (short)vm_atoi_16(valid_str(vm, cr->position + 4, 4));
		replace_map(vm, (cr->position + (s % IDX_MOD) * 2) % 8192,
		vm_itoa_16(cr->regist[f]), 8);
	}
	else if (args[0] == T_REG && args[1] == T_REG)
	{
		s = (unsigned char)vm_atoi_16(valid_str(vm, cr->position + 4, 2));
		cr->regist[s] = f;
	}
	if (args[0] == T_REG && (args[1] == T_REG || args[1] == T_IND))
		print_st(cr, f, s, args[1]);
	cr->position = perehod(args, cr);
}
