/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshreder <vshreder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 14:38:29 by yyakoven          #+#    #+#             */
/*   Updated: 2019/03/24 16:03:57 by vshreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int						find_instruction_id(char *name)
{
	int					i;

	i = 0;
	while (g_optab[i].name != 0)
	{
		if (ft_strequ(g_optab[i].name, name))
			return (g_optab[i].index);
		i++;
	}
	return (-1);
}

int						skip_valid_char(char *line, int mode)
{
	int					i;

	i = 0;
	while (line[i])
	{
		if (line[i] == HSH)
			return (ft_strlen(line));
		if (line[i] != SPACE && line[i] != TAB && line[i] != NL)
		{
			if (mode == 0)
				return (i);
			if (mode == 1)
			{
				if (!ft_strchr(LABEL_CHARS, line[i]))
					return (i);
			}
			if (mode == 2)
			{
				if (!ft_isdigit(line[i]))
					return (i);
			}
		}
		i++;
	}
	return (-1);
}

void					init_plr_args(char *line, t_plr *plr, int savei, int c)
{
	if (c == 2)
		plr->cur_args[2] = ft_strsub(line, savei + 1, plr->boi - savei - 1);
	if (c == 0)
		plr->cur_args[0] = ft_strsub(line, 0, plr->boi);
	if (c == 1)
		plr->cur_args[1] = ft_strsub(line, savei + 1, plr->boi - savei - 1);
}

int						check_arg_num(char *line, int arg_num, t_plr *plr)
{
	int					c;
	int					k;

	c = 0;
	plr->boi = skip_valid_char(line, 0);
	k = plr->boi;
	while (line[plr->boi] && line[plr->boi] != COMMENT_CHAR)
	{
		if (line[plr->boi] == SEPARATOR_CHAR)
		{
			if (++c == 1)
			{
				plr->cur_args[0] = ft_strsub(line + k, 0, plr->boi - k);
				k = plr->boi;
			}
			else if (c == 2)
			{
				plr->cur_args[1] = ft_strsub(line + k + 1, 0, plr->boi - k - 1);
				k = plr->boi;
			}
		}
		plr->boi++;
	}
	init_plr_args(line, plr, k, c);
	return (c == arg_num - 1) ? 1 : 0;
}
