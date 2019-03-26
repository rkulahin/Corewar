/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_labels.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakoven <yyakoven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 11:28:54 by vshreder          #+#    #+#             */
/*   Updated: 2019/03/25 19:12:05 by yyakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int						match_label(char *label, t_plr *plr,
						t_instr *cur_in, int index)
{
	t_label				*cur_l;
	int					num;

	cur_l = plr->label;
	num = 0;
	while (cur_l)
	{
		if (ft_strequ(cur_l->name, label + 1))
		{
			if (cur_l->instr)
				num = cur_l->instr->total_bytes - cur_in->total_bytes;
			else
				num = g_bytes - cur_in->total_bytes;
			ft_strdel(&cur_in->args[index]);
			cur_in->args[index] = ft_itoa(num);
			return (1);
		}
		cur_l = cur_l->next;
	}
	return (0);
}

void					apply_labels(t_plr *plr)
{
	t_instr				*cur_in;
	int					i;

	cur_in = plr->instr;
	i = 0;
	while (cur_in)
	{
		while (i < g_optab[cur_in->code - 1].num_arg)
		{
			if (cur_in->args[i][0] == LABEL_CHAR)
			{
				if (!match_label(cur_in->args[i], plr, cur_in, i))
					e2("A label passed havin' trouble finding its match...",
					"I bet you know that feeling  ( ͡~ ͜ʖ ͡°)");
			}
			i++;
		}
		i = 0;
		cur_in = cur_in->next;
	}
}

int						read_file(int fd, t_plr *plr)
{
	char				*line;

	line = NULL;
	read_commands(fd, plr, &line);
	read_execution(fd, plr, &line);
	if (!plr->label && !plr->instr)
		e2("Seems like no instruction is here...",
		"like on the condom your father used");
	apply_labels(plr);
	return (0);
}
