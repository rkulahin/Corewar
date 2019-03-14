/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_parce.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 09:21:59 by rkulahin          #+#    #+#             */
/*   Updated: 2019/03/14 14:53:27 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		valid_log(t_vm *all, int ac, char **av, int i)
{
	int		index;

	if (i >= ac - 1)
		error("BAD_LOG_INDEX");
	index = ft_atoi(av[i + 1]);
	if (index <= 0 || index > 32 || !str_of_num(av[i + 1]))
		error("BAD_LOG_INDEX");
	if (all->nbr_log != 0)
		error("SECOND_LOG_INDEX");
	all->nbr_log = index;
	return (i + 2);
}

int		valid_aff(t_vm *all, int i)
{
	all->aff = 1;
	return (i + 1);
}

int		valid_curses(t_vm *all, int i)
{
	all->curses = 1;
	return (i + 1);
}

void	print_usage(void)
{
	ft_printf("Usage: ./corewar [-dump N -v N -a | -p]");
	ft_printf(" -n N <champion1.cor> <...>\n");
	ft_printf("-a        : Prints output from \"aff\"");
	ft_printf(" (Default is to hide it)\n");
	ft_printf("-v N      : Verbosity levels,");
	ft_printf(" can be added together to enable several\n");
	ft_printf("		- 1 : Show lives\n");
	ft_printf("		- 2 : Show cycles\n");
	ft_printf("		- 4 : Show operations (Params are NOT litteral ...)\n");
	ft_printf("		- 8 : Show deaths\n");
	ft_printf("		- 16 : Show PC movements (Except for jumps)\n");
	ft_printf("-c        : Ncurses output mode\n");
	exit(1);
}

void		init_curses(void)
{
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, true);
	curs_set(0);
	start_color();
	init_pair(1, 8, COLOR_BLACK);
	init_pair(2, COLOR_CYAN, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(5, COLOR_YELLOW, COLOR_BLACK);
	init_pair(6, 8, 8);
	init_pair(7, COLOR_BLACK, COLOR_CYAN);
	init_pair(8, COLOR_BLACK, COLOR_RED);
	init_pair(9, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(10, COLOR_BLACK, COLOR_YELLOW);
	init_pair(11, COLOR_CYAN, COLOR_CYAN);
	init_pair(12, COLOR_RED, COLOR_RED);
	init_pair(13, COLOR_MAGENTA, COLOR_MAGENTA);
	init_pair(14, COLOR_YELLOW, COLOR_YELLOW);
	nodelay(stdscr, TRUE);
}

void	null_flags(t_vm *vm)
{
	vm->aff = 0;
	vm->nbr_log = 0;
	vm->nbr_cycles = 0;
}
