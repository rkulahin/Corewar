/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   curses.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:05:57 by rkulahin          #+#    #+#             */
/*   Updated: 2019/03/15 16:49:27 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			visual_menu(t_vm *vm)
{
	int			i;
	t_players	*tmp;

	i = 20;
	mvprintw(i, 128 + 128 / 2 + 10, ">> PAUSED <<");
	mvprintw(++i, 128 + 128 / 2 + 10, "Cycles/second limit : 50");
	mvprintw(++i, 128 + 128 / 2 + 10, "Cycle : %d", vm->cycle);
	mvprintw(++i, 128 + 128 / 2 + 10, "Processes : %d", vm->nbr_car - 1);
	i += 2;
	tmp = vm->players;
	while (tmp)
	{
		mvaddch(++i, 128 + 128 / 2 + 8, '-' | COLOR_PAIR(tmp->index + 1) | A_BOLD);
		mvaddch(i, 128 + 128 / 2 + 7, '-' | COLOR_PAIR(tmp->index + 1) | A_BOLD);
		mvprintw(i, 128 + 128 / 2 + 10, "Player %d : %s",
		tmp->index, tmp->champ->prog_name);
		tmp = tmp->next;
	}
	i += 2;
	mvprintw(++i, 128 + 128 / 2 + 10, "Cycle to Die : %d", vm->die);
	mvprintw(++i, 128 + 128 / 2 + 10, "Cycle Delta : %d", CYCLE_DELTA);
	mvprintw(++i, 128 + 128 / 2 + 10, "NBR LIVE : %d", vm->live);
	mvprintw(++i, 128 + 128 / 2 + 10, "NBR CHECKS : %d", vm->nbr_checks);
}

static int			*find_x_y(int position)
{
	int *coord;

	coord = (int *)malloc(sizeof(int) + 4);
	position += position / 2 - 1;
	coord[0] = position % 192;
	coord[1] = (position / 192) % 64 + 1;
	coord[2] = (position + 1) % 192;
	coord[3] = ((position + 1) / 192) % 64 + 1;
	return (coord);
}

void			recolor_map(t_vm *vm, int position, int nb, int color)
{
	int		i;
	int		j;
	int		*coord;

	i = 0;
	j = 0;
	if (position < 0)
		position = position + 8192;
	while (i < nb)
	{
		vm->color[(j + position) % 8192] = color;
		vm->color[(j + position + 1) % 8192] = color;
		coord = find_x_y(position + i + 1);
		mvaddch(coord[1], coord[0], vm->map[(j + position) % 8192] | COLOR_PAIR(color) | A_BOLD);
		mvaddch(coord[3], coord[2], vm->map[(j + position + 1) % 8192] | COLOR_PAIR(color) | A_BOLD);
		i += 2;
		j += 2;
		free(coord);
	}
}

void			delete_cr(t_vm *vm)
{
	t_carriage	*tmp;
	int			*coord;

	tmp = vm->carriage;
	while (tmp)
	{
		if (vm->color[tmp->position % 8192] > 6 && vm->color[tmp->position % 8192] < 11)
		{
			coord = find_x_y(tmp->position + 1);
			mvaddch(coord[1], coord[0], vm->map[(tmp->position) % 8192] | COLOR_PAIR(vm->color[tmp->position % 8192] - 5) | A_BOLD);
			mvaddch(coord[3], coord[2], vm->map[(tmp->position + 1) % 8192] | COLOR_PAIR(vm->color[(tmp->position + 1) % 8192] - 5) | A_BOLD);
			vm->color[(tmp->position) % 8192] = vm->color[tmp->position % 8192] - 5;
			vm->color[(tmp->position + 1) % 8192] = vm->color[(tmp->position + 1) % 8192] - 5;
			free(coord);
		}
		tmp = tmp->next;
	}
}

void			print_cr(t_vm *vm)
{
	t_carriage	*tmp;
	int			*coord;

	tmp = vm->carriage;
	while (tmp)
	{
		if (vm->color[tmp->position % 8192] > 1 && vm->color[tmp->position % 8192] < 6)
		{
			coord = find_x_y(tmp->position + 1);
			mvaddch(coord[1], coord[0], vm->map[(tmp->position) % 8192] | COLOR_PAIR(vm->color[tmp->position % 8192] + 5));
			mvaddch(coord[3], coord[2], vm->map[(tmp->position + 1) % 8192] | COLOR_PAIR(vm->color[(tmp->position + 1) % 8192] + 5));
			vm->color[(tmp->position) % 8192] = vm->color[tmp->position % 8192] + 5;
			vm->color[(tmp->position + 1) % 8192] = vm->color[(tmp->position + 1) % 8192] + 5;
			free(coord);
		}
		tmp = tmp->next;
	}
}

void			visual_map(t_vm *vm)
{
	int			i;

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
	visual_menu(vm);
}
