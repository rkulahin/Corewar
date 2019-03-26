/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshreder <vshreder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 14:36:12 by yyakoven          #+#    #+#             */
/*   Updated: 2019/03/23 18:06:42 by vshreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int						g_lnstp;

void					translate_int(int fd, int arg, int num)
{
	unsigned char		*cp;
	int					i;

	i = 0;
	cp = (unsigned char *)&arg + num - 1;
	while (i++ < num)
	{
		write(fd, cp, 1);
		cp--;
	}
}

void					translate_char(int fd, unsigned char arg, int num)
{
	write(fd, &arg, num);
}

void					write_name(int fd, char *name, int mode)
{
	int					i;
	int					rest;

	i = 0;
	while (name[i])
	{
		translate_char(fd, (unsigned char)name[i], 1);
		i++;
	}
	if (mode == 1)
		rest = PROG_NAME_LENGTH - i;
	else
		rest = COMMENT_LENGTH - i;
	while (rest > 0)
	{
		translate_char(fd, 0, 1);
		rest--;
	}
}

t_plr					*init_plr(void)
{
	t_plr				*plr;

	plr = (t_plr *)malloc(sizeof(t_plr));
	if (plr)
	{
		plr->name = NULL;
		plr->comment = NULL;
		plr->done = -1;
		plr->ins_num = 0;
		plr->label = NULL;
		plr->instr = NULL;
		plr->last = NULL;
		plr->filename = NULL;
		plr->cur_args[0] = NULL;
		plr->cur_args[1] = NULL;
		plr->cur_args[2] = NULL;
		plr->args = NULL;
		plr->output = NULL;
	}
	return (plr);
}

int						main(int argc, char **argv)
{
	int					fd_cor;
	int					fd_s;
	t_plr				*plr;

	g_lnstp = 0;
	g_bytes = 0;
	plr = init_plr();
	plr->filename = open_file(argc, argv, &fd_s);
	read_file(fd_s, plr);
	create_file(&fd_cor, plr->filename);
	translate_int(fd_cor, COREWAR_EXEC_MAGIC, 4);
	write_name(fd_cor, plr->name, 1);
	translate_int(fd_cor, 0, 4);
	translate_int(fd_cor, g_bytes, 4);
	write_name(fd_cor, plr->comment, 2);
	translate_int(fd_cor, 0, 4);
	encode(plr->instr, fd_cor);
	return (0);
}
