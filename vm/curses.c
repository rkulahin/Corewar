/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   curses.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:05:57 by rkulahin          #+#    #+#             */
/*   Updated: 2019/03/14 16:14:22 by rkulahin         ###   ########.fr       */
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
		i += 2;
	}
	printw("\nCYCLE = %d\n", vm->cycle);
	//sleep(1);
}

void			recolor_map(t_vm *vm, int position, int nb, int color)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < nb + (nb / 2 - 1))
	{
		mvaddch(((position + i) / 128) % 64 + 1, (position + i) % 128 + (((position) % 128) / 2), vm->map[(j + position) % 8192] | COLOR_PAIR(color) | A_BOLD);
		mvaddch(((position + i) / 128) % 64 + 1, (position + i) % 128 + (((position) % 128) / 2 + 1), vm->map[(j + position + 1) % 8192] | COLOR_PAIR(color) | A_BOLD);
		i += 3;
		j += 2;
	}
}