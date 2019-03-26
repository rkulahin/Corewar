/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakoven <yyakoven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:42:30 by yyakoven          #+#    #+#             */
/*   Updated: 2019/03/25 19:10:20 by yyakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void			check_for_validity(char *ptr)
{
	ptr = skip_whitespace(ptr);
	if (*ptr && *ptr != COMMENT_CHAR)
		e2("Another stupid error...",
				"another stupid user");
}

int				get_command_type(char *ptr)
{
	int			name;

	name = 0;
	if (ft_strnequ(ptr, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
		name = ft_strlen(NAME_CMD_STRING);
	else if (ft_strnequ(ptr, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)))
		name = ft_strlen(COMMENT_CMD_STRING);
	if (name == 0)
		e2("This file is missing name/comment...",
				"and you are missing a brain");
	return (name);
}

void			check_length(t_plr *plr)
{
	if (ft_strlen(plr->name) > PROG_NAME_LENGTH)
		e2("Name is too long...",
		"Your life must be exciting if you have time for that shit");
	if (ft_strlen(plr->comment) > COMMENT_LENGTH)
		e2("Comment is too long...",
		"Your life must be exciting if you have time for that shit");
}
