/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshreder <vshreder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:41:11 by yyakoven          #+#    #+#             */
/*   Updated: 2019/03/22 19:40:57 by vshreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int						is_empty(char *line)
{
	int					i;

	i = 0;
	while (line && line[i])
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

int						is_comment(char *line)
{
	int					i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
	{
		i++;
	}
	if (line[i] == COMMENT_CHAR)
		return (1);
	return (0);
}

char					*skip_whitespace(char *line)
{
	char				*ptr;

	ptr = line;
	while (*ptr && (*ptr == ' ' || *ptr == '\t'))
	{
		g_lnstp++;
		ptr++;
	}
	return (ptr);
}

void					skip_empty_lines(int fd, char **line)
{
	if (*line && !is_comment(*line) && !is_empty(*line))
		return ;
	ft_strdel(line);
	while (get_next_line(fd, line))
	{
		if (!is_comment(*line) && !is_empty(*line))
			break ;
		free(*line);
	}
}
