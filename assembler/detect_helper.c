/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakoven <yyakoven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 18:52:10 by vshreder          #+#    #+#             */
/*   Updated: 2019/03/25 19:12:08 by yyakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int						valid_arg(char *str, int mode)
{
	int					i;

	i = 0;
	while (str[i])
	{
		if ((mode == 1 && ft_isdigit(str[i])) ||
					(str[i] == TAB || str[i] == SPACE))
			i++;
		else if ((mode == 2 && ft_strchr(LABEL_CHARS, str[i])) ||
					(str[i] == TAB || str[i] == SPACE))
			i++;
		else
			return (0);
	}
	return (1);
}

static int				skip_blank_minus(char **str, int *mda)
{
	int					i;

	i = 0;
	*mda = 0;
	*str = skip_whitespace(*str);
	if ((*str)[i] == LABEL_CHAR || (*str)[i] == DIRECT_CHAR)
	{
		if ((*str)[i + 1] == '-' && (*str)[i + 2] && ft_isdigit((*str)[i + 2]))
		{
			(*str)++;
			*mda = 1;
		}
	}
	return (i);
}

char					*send_nudes(char *str)
{
	int					i;
	int					mda;
	int					temp;
	char				*tmp;

	tmp = NULL;
	i = skip_blank_minus(&str, &mda);
	while (str[i] && str[i] != SPACE && str[i] != TAB)
	{
		if ((str[0] == '-' && str[0 + 1] && ft_isdigit(str[0 + 1])) ||
			(ft_strchr(LABEL_CHARS, str[i]) || ft_isalnum(str[i]) ||
			str[i] == LABEL_CHAR || str[i] == DIRECT_CHAR))
			i++;
		else
			e2("Some args's characters are illegal...",
			"I won't process it, but you can name your son so");
	}
	temp = i + mda;
	while (str[i] && (str[i] == SPACE || str[i] == TAB))
		i++;
	(str[i]) ? e2("Some args's characters are illegal...",
		"I won't process it, but you can name your son so") : 0;
	(mda == 1) ? str-- : 0;
	tmp = ft_strsub(str, 0, temp + mda);
	return (tmp);
}

int						detect_direct_char(char *cmd, t_instr *instr, int index)
{
	if (cmd[1] == LABEL_CHAR && valid_arg(cmd + 2, 2))
		instr->args[index] = ft_strdup(cmd + 1);
	else if (cmd[1] == '-' && valid_arg(cmd + 2, 1))
		instr->args[index] = ft_strdup(cmd + 1);
	else if (cmd[1] && valid_arg(cmd + 1, 1))
		instr->args[index] = ft_strdup(cmd + 1);
	else
	{
		ft_strdel(&cmd);
		return (0);
	}
	instr->arg_codes[index] = DIR_CODE;
	ft_strdel(&cmd);
	return (1);
}

int						detect_indi_char(char *cmd, t_instr *instr, int index)
{
	if (((ft_isdigit(cmd[0]) && valid_arg(cmd + 1, 1)) ||
	(cmd[0] == LABEL_CHAR && valid_arg(cmd + 1, 2))) ||
	(cmd[0] == '-' && valid_arg(cmd + 1, 1)))
	{
		instr->arg_codes[index] = IND_CODE;
		instr->args[index] = ft_strdup(cmd);
		ft_strdel(&cmd);
		return (1);
	}
	return (0);
}
