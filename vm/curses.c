/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   curses.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:05:57 by rkulahin          #+#    #+#             */
/*   Updated: 2019/03/14 14:15:17 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			visual_map(t_vm *vm)
{
	int		i;

	i = 0;
	while (i < MEM_SIZE * 2)
	{
		if (i % 128 == 0)
			printw("\n");
		addch(vm->map[i] | COLOR_PAIR(vm->color[i]));
		addch(vm->map[i + 1] | COLOR_PAIR(vm->color[i + 1]));
		addch(' ');
		i += 4;
	}
	printw("\nCYCLE = %d\n", vm->cycle);
	// sleep(1);
}
