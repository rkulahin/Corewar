/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 14:36:08 by rkulahin          #+#    #+#             */
/*   Updated: 2019/02/28 14:24:03 by rkulahin         ###   ########.fr       */
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
	// int		i;
	// int		b;

	args = check_arg(vm_atoi_16(valid_str(vm, cr->position, 2)));
	ff = valid_str(vm, cr->position + 2, 2);
	f = (unsigned char)vm_atoi_16(ff);
	// if (f == 0)
	// {
	// 	ft_printf("%i %i\n", cr->position / 128, cr->position % 128);
	// 	ft_printf("cycle %i\n", vm->cycle);
	// 				ft_printf("MAP :\n");
	// i = -1;
	// b = -1;
	// while (++i < MEM_SIZE * 2)
	// {
	// 	if ((i % 128) == 0)
	// 	{
	// 		ft_printf("\n");
	// 		ft_printf("line = %d|  ", ++b);
	// 	}
	// 	if (i == 7924)
	// 		ft_printf(YEL"L"EOC);
	// 	if (i == 0 || i == 1)
	// 		ft_printf(RED"%c"EOC, vm->map[i]);
	// 	else if (i == (MEM_SIZE * 2) / vm->nbr_plrs || i == (MEM_SIZE * 2) / vm->nbr_plrs + 1)
	// 		ft_printf(YEL"%c"EOC, vm->map[i]);
	// 	else if (i == ((MEM_SIZE * 2) / vm->nbr_plrs) * 2 || i == ((MEM_SIZE * 2) / vm->nbr_plrs) * 2 + 1)
	// 		ft_printf(BLU"%c"EOC, vm->map[i]);
	// 	else if (i == ((MEM_SIZE * 2) / vm->nbr_plrs) * 3 || i == ((MEM_SIZE * 2) / vm->nbr_plrs) * 3 + 1)
	// 		ft_printf(GRE"%c"EOC, vm->map[i]);
	// 	else if (i <= 1225)
	// 		ft_printf(RED"%c"EOC, vm->map[i]);
	// 	else
	// 		ft_printf("%c", vm->map[i]);
	// }
	// ft_printf("\nsize = %d\n", i);
	// exit(1);
	// }
	if (f <= 0 || f > 16)
	{
		cr->position = perehod(args, cr);
		return ;
	}
	if (args[0] == T_REG && args[1] == T_IND)
	{
		s = (short)vm_atoi_16(valid_str(vm, cr->position + 4, 4));
		replace_map(vm, (cr->position + (s % IDX_MOD) * 2) % 8192,
		vm_itoa_16(cr->regist[f - 1]), 8);
	}
	else if (args[0] == T_REG && args[1] == T_REG)
	{
		s = (unsigned char)vm_atoi_16(valid_str(vm, cr->position + 4, 2));
		cr->regist[s - 1] = f;
	}
	if ((args[0] == T_REG && (args[1] == T_REG || args[1] == T_IND)) && ((vm->nbr_log & 4) == 4))
		print_st(cr, f, s, args[1]);
	cr->position = perehod(args, cr);
}
