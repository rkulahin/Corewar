/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakoven <yyakoven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 14:36:12 by yyakoven          #+#    #+#             */
/*   Updated: 2019/03/25 19:12:58 by yyakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

char					*ft_strappend(char **s1, char **s2)
{
	char				*tmp;

	tmp = ft_strjoin(*s1, *s2);
	free(*s1);
	free(*s2);
	*s1 = tmp;
	return (*s1);
}

void					fetch_name(t_plr *plr, int fd, char **line, char **str)
{
	while (!plr->done)
	{
		ft_strdel(line);
		plr->args = ft_strdup("\n");
		*str = ft_strappend(str, &(plr->args));
		if (get_next_line(fd, line))
		{
			plr->args = *line;
			while (*(plr->args))
			{
				if (*(plr->args) == '"')
				{
					plr->done = 1;
					check_for_validity(plr->args + 1);
					break ;
				}
				plr->args++;
			}
			plr->args = ft_strsub(*line, 0, plr->args - *line);
			*str = ft_strappend(str, &plr->args);
		}
		else
			e2("Sadly, you lost one quote...",
			"one more mistake and you'll be losing something else");
	}
}

void					save_data(char *str, t_plr *plr, int type)
{
	if (type == 5)
		plr->name = str;
	else
		plr->comment = str;
}

void					read_command(int fd, t_plr *plr, char **line)
{
	char				*ptr;
	char				*ptr1;
	char				*str;
	int					type;

	ptr = skip_whitespace(*line);
	type = get_command_type(ptr);
	ptr = skip_whitespace(ptr + type);
	if (*ptr != '"')
		e2("Name/cmmnt's missing...", "I bet ur parents wish to be missing u");
	plr->done = 0;
	ptr1 = ptr + 1;
	while (*(++ptr))
	{
		if (*ptr == '"')
		{
			plr->done = 1;
			check_for_validity(ptr + 1);
			break ;
		}
	}
	str = ft_strsub(ptr1, 0, ptr - ptr1);
	if (!plr->done)
		fetch_name(plr, fd, line, &str);
	save_data(str, plr, type);
}

void					read_commands(int fd, t_plr *plr, char **line)
{
	int					i;

	i = 0;
	while (i < 2)
	{
		skip_empty_lines(fd, line);
		if (*line)
			read_command(fd, plr, line);
		else
			e2("The file is empty...", "just like your head is");
		i++;
		ft_strdel(line);
	}
	check_length(plr);
}
