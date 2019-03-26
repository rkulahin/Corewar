/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_lbl_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakoven <yyakoven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 14:19:45 by vshreder          #+#    #+#             */
/*   Updated: 2019/03/25 19:10:20 by yyakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void					pss_maybe_some_problems(t_plr *plr, char **line)
{
	if ((plr->args = ft_strsub(*line, g_lnstp, ft_strlen(*line))) &&
					!*(skip_whitespace(plr->args)))
		e2("It looks like this instruction lost its arguments...",
			"so sad your parents tried but couldn't lose you");
}

t_instr					*come_here_baby_instruction(char *str, t_plr *plr,
						char **line)
{
	t_instr				*inst;

	pss_maybe_some_problems(plr, line);
	inst = create_instr(str);
	add_instr(inst, plr);
	process_instr(inst, plr);
	if (plr->args)
		ft_strdel(&(plr->args));
	return (inst);
}

void					come_here_baby_label(char **line, int fd)
{
	ft_strdel(line);
	get_next_line(fd, line);
	skip_empty_lines(fd, line);
}

t_label					*hey_baby_label(char *str, t_plr *plr)
{
	t_label				*l;

	l = create_label(str);
	add_label(l, &(plr->label));
	return (l);
}

t_instr					*search_for_instr_or_label(int fd, char **line,
						t_plr *plr)
{
	t_label				*l;
	char				*sed_line;
	char				*str;

	g_lnstp = 0;
	if ((str = is_instruction(*line)))
		return (come_here_baby_instruction(str, plr, line));
	else if ((str = is_label(line)))
	{
		l = hey_baby_label(str, plr);
		if (!*(plr->c = skip_whitespace(*line + g_lnstp + 1)) || *plr->c == HSH)
		{
			come_here_baby_label(line, fd);
			if (*line)
				return (l->instr = search_for_instr_or_label(fd, line, plr));
		}
		else
		{
			sed_line = ft_strsub(*line, g_lnstp + 1, ft_strlen(*line));
			l->instr = search_for_instr_or_label(fd, &sed_line, plr);
			ft_strdel(&sed_line);
			return (l->instr);
		}
	}
	return (NULL);
}
