/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:28:39 by rkulahin          #+#    #+#             */
/*   Updated: 2019/03/02 14:15:06 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int			find_ind(t_vm *vm, int pc, char *str)
{
	int		t_ind;
	int		nb;

	nb = (short)vm_atoi_16(str);
	t_ind = vm_atoi_16(valid_str(vm, pc - 2 + nb, 8));
	return (t_ind);
}

static int			check_ar(int **ar)
{
	int		i;
	int		j;

	j = 1;
	i = -1;
	while (++i < 2)
	{
		if (ar[0][i] == 1)
			ar[0][i] = -1;
		else if (ar[0][i] > 1 && ar[0][i] < 17)
			ar[0][i] = 0;
		else
			j = 0;
	}
	if (ar[0][2] <= 0 || ar[0][2] >= 17)
		j = 0;
	return (j);
}

static int			*save_arg(int *j, t_vm *vm, t_carriage *cr, int *args)
{
	int		i;
	int		*ar;

	i = -1;
	ar = (int *)malloc(sizeof(int) * 4);
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
	if (ar[0] == 0 || ar[1] == 0)
		ar[0] = 100;
	return (ar);
}

void				op_and(t_vm *vm, t_carriage *cr)
{
	char	*str_cotage;
	int		*args;
	int		*ar;
	int		j;

	j = 0;
	str_cotage = valid_str(vm, cr->position, 2);
	args = check_arg(vm_atoi_16(str_cotage));
	ar = save_arg(&j, vm, cr, args);
	if (args[0] != 0 && args[1] != 0 && args[2] == T_REG)
	{
		if (check_ar(&ar))
		{
			cr->regist[ar[2] - 1] = ar[0] & ar[1];
			cr->carry = (cr->regist[ar[2] - 1] == 0 ? 1 : 0);
			if ((vm->nbr_log & 4) == 4)
				ft_printf("P%5i | and %i %i r%i\n",
				cr->index, ar[0], ar[1], ar[2]);
		}
	}
	cr->position = cr->position + j + 4;
}

void				op_or(t_vm *vm, t_carriage *cr)
{
	char	*str_cotage;
	int		*args;
	int		*ar;
	int		j;

	j = 0;
	str_cotage = valid_str(vm, cr->position, 2);
	args = check_arg(vm_atoi_16(str_cotage));
	ar = save_arg(&j, vm, cr, args);
	if (args[0] != 0 && args[1] != 0 && args[2] == T_REG)
	{
		if (check_ar(&ar))
		{
			cr->regist[ar[2] - 1] = ar[0] | ar[1];
			cr->carry = (cr->regist[ar[2] - 1] == 0 ? 1 : 0);
			if ((vm->nbr_log & 4) == 4)
				ft_printf("P%5i | or %i %i r%i\n",
				cr->index, ar[0], ar[1], ar[2]);
		}
	}
	cr->position = cr->position + j + 4;
}

void				op_xor(t_vm *vm, t_carriage *cr)
{
	char	*str_cotage;
	int		*args;
	int		*ar;
	int		j;

	j = 0;
	str_cotage = valid_str(vm, cr->position, 2);
	args = check_arg(vm_atoi_16(str_cotage));
	ar = save_arg(&j, vm, cr, args);
	if (args[0] != 0 && args[1] != 0 && args[2] == T_REG)
	{
		if (check_ar(&ar))
		{
			cr->regist[ar[2] - 1] = ar[0] ^ ar[1];
			cr->carry = (cr->regist[ar[2] - 1] == 0 ? 1 : 0);
			if ((vm->nbr_log & 4) == 4)
				ft_printf("P%5i | xor %i %i r%i\n",
				cr->index, ar[0], ar[1], ar[2]);
		}
	}
	cr->position = cr->position + j + 4;
}
