/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   curses2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 11:32:05 by rkulahin          #+#    #+#             */
/*   Updated: 2019/03/19 15:26:58 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			visual_menu(t_vm *vm, int sleep, int i)
{
	t_players	*tmp;

	mvprintw(i, 128 + 128 / 2 + 10, ">> PAUSED <<");
	mvprintw(++i, 128 + 128 / 2 + 10, "Cycles/second : %-8d", sleep);
	mvprintw(++i, 128 + 128 / 2 + 10, "Cycle : %-8d", vm->cycle);
	mvprintw(++i, 128 + 128 / 2 + 10, "Processes : %-8d", vm->nbr_car - 1);
	i += 2;
	tmp = vm->players;
	while (tmp)
	{
		mvaddch(++i, 128 + 128 / 2 + 8,
		'-' | COLOR_PAIR(tmp->index + 1) | A_BOLD);
		mvaddch(i, 128 + 128 / 2 + 7,
		'-' | COLOR_PAIR(tmp->index + 1) | A_BOLD);
		mvprintw(i, 128 + 128 / 2 + 10, "Player %d : %s",
		tmp->index, tmp->champ->prog_name);
		tmp = tmp->next;
	}
	i += 2;
	mvprintw(++i, 128 + 128 / 2 + 10, "Cycle to Die : %-8d", vm->die);
	mvprintw(++i, 128 + 128 / 2 + 10, "Cycle Delta : %-8d", CYCLE_DELTA);
	mvprintw(++i, 128 + 128 / 2 + 10, "NBR LIVE : %-8d", vm->live);
	mvprintw(++i, 128 + 128 / 2 + 10, "NBR CHECKS : %-8d", vm->nbr_checks);
}

int				control_curses(int sleep, t_vm *vm, int key)
{
	if (vm->curses == 0)
		return (1);
	key = getch();
	visual_menu(vm, sleep, 20);
	if (sleep == -1)
		sleep = 0;
	if (key == KEY_BTAB)
		sleep = 0;
	if (key == KEY_UP && sleep == 0)
		sleep = -1;
	else if (key == KEY_LEFT && sleep >= 0 && sleep <= 999)
		sleep += 1;
	else if (key == KEY_DOWN && sleep >= 0 && sleep <= 990)
		sleep += 10;
	else if (key == KEY_RIGHT && sleep >= 0 && sleep <= 900)
		sleep += 100;
	if (sleep != 0)
		mvprintw(20, 128 + 128 / 2 + 10, ">> >RUN< << ");
	else
		mvprintw(20, 128 + 128 / 2 + 10, ">> PAUSED <<");
	if (sleep > 0 && sleep != 1000)
		usleep(1000000 / sleep);
	return (sleep);
}

void			prnt_instruction(void)
{
	int		i;

	i = 35;
	mvprintw(i, 128 + 128 / 2 + 10, "...INSTRUCTION...");
	mvprintw(++i, 128 + 128 / 2 + 10, "RUN ++1 -----> KEY_LEFT");
	mvprintw(++i, 128 + 128 / 2 + 10, "RUN ++10 ----> KEY_DOWN");
	mvprintw(++i, 128 + 128 / 2 + 10, "RUN ++100 ---> KEY_RIGHT");
	mvprintw(++i, 128 + 128 / 2 + 10, "GO ONE STEP -> KEY_UP");
	mvprintw(++i, 128 + 128 / 2 + 10, "[STOP] ------> SHIFT + TAB");
}

void			print_usage(void)
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
