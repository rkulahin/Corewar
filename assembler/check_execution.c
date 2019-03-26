/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakoven <yyakoven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 19:38:23 by vshreder          #+#    #+#             */
/*   Updated: 2019/03/25 19:12:06 by yyakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void					read_execution(int fd, t_plr *plr, char **line)
{
	plr->instr = NULL;
	plr->label = NULL;
	while (1)
	{
		skip_empty_lines(fd, line);
		if (*line && *(skip_whitespace(*line)) == '.')
			e2("This command isn't allowed...",
					"Am I a joke to you??? READ MAN");
		if (*line == NULL)
			break ;
		search_for_instr_or_label(fd, line, plr);
		ft_strdel(line);
		if ((get_next_line(fd, line)) != 1)
			break ;
	}
}

char					*is_label(char **line)
{
	char				*ptr;
	char				*ptr1;
	char				*label;

	g_lnstp = 0;
	ptr = skip_whitespace(*line);
	ptr1 = ptr;
	while (ft_strchr(LABEL_CHARS, *ptr1))
	{
		g_lnstp++;
		ptr1++;
	}
	if (*ptr1 != LABEL_CHAR || g_lnstp == 0)
	{
		e2("Illegal label ... ", "I'm calling the police");
	}
	label = ft_strsub(ptr, 0, ptr1 - ptr);
	return (label);
}

char					*is_instruction(char *line)
{
	char				*p;
	char				*p1;
	char				*instr;

	p = skip_whitespace(line);
	p1 = p;
	while (ft_isalpha(*p1))
	{
		g_lnstp++;
		p1++;
	}
	instr = ft_strsub(p, 0, p1 - p);
	if (find_instruction_id(instr) >= 0)
	{
		if (*p && *p1 && *p1 != SPACE && *p1 != TAB && *p1 != DIRECT_CHAR &&
		*p1 != '-')
		{
			ft_strdel(&instr);
			return (0);
		}
		if (*p1 != LABEL_CHAR)
			return (instr);
	}
	ft_strdel(&instr);
	return (0);
}
