/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 17:23:57 by rkulahin          #+#    #+#             */
/*   Updated: 2019/03/17 17:25:58 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		print_sti(int *t_args, t_carriage *cr)
{
	ft_printf("P %4i | sti r%i %i %i\n", cr->index,
	t_args[0], t_args[1], t_args[2]);
	ft_printf("       | -> store to %i + %i = %i (with pc and mod %i)\n",
	t_args[1], t_args[2], t_args[1] + t_args[2],
	(cr->position / 2) + ((t_args[1] + t_args[2]) % IDX_MOD));
}

void		print_v4(t_carriage *cr, int *ar)
{
	ft_printf("P %4d | ldi %d %d r%d\n", cr->index, ar[0], ar[1], ar[2]);
	ft_printf("       | -> load from %d + %d = %d (with pc and mod %d)\n",
	ar[0], ar[1], ar[0] + ar[1],
	(((ar[0] + ar[1]) % IDX_MOD) + cr->position / 2) % 4096);
}

void		print_lldi(t_carriage *cr, int *ar)
{
	ft_printf("P %4d | lldi %d %d r%d\n", cr->index, ar[0], ar[1], ar[2]);
	ft_printf("       | -> load from %d + %d = %d (with pc %d)\n",
	ar[0], ar[1], ar[0] + ar[1], (ar[0] + ar[1] + cr->position / 2) % 4096);
}
