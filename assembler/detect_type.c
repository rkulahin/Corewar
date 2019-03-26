/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakoven <yyakoven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 18:50:30 by vshreder          #+#    #+#             */
/*   Updated: 2019/03/25 19:10:20 by yyakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int						detect_type(char *str, t_instr *instr, int index)
{
	char				*cmd;

	cmd = send_nudes(str);
	if (cmd[0] == 'r')
	{
		if (valid_arg(cmd + 1, 1) && ft_atoi(cmd + 1) < 100 &&
			ft_atoi(cmd + 1) > 0)
		{
			instr->arg_codes[index] = REG_CODE;
			instr->args[index] = ft_strdup(cmd + 1);
			ft_strdel(&cmd);
			if (ft_strlen(instr->args[index]) <= 3)
				return (1);
		}
	}
	else if (cmd[0] == DIRECT_CHAR)
		return (detect_direct_char(cmd, instr, index));
	else if (cmd[0] == LABEL_CHAR || ft_isdigit(cmd[0]) || cmd[0] == '-')
	{
		if (detect_indi_char(cmd, instr, index))
			return (1);
	}
	if (cmd)
		ft_strdel(&cmd);
	return (0);
}

void					count_bytes(t_instr *instr)
{
	int					sum;
	int					i;

	sum = 1;
	i = 0;
	instr->total_bytes = g_bytes;
	while (i < g_optab[instr->code - 1].num_arg)
	{
		if (instr->arg_codes[i] == 2)
			sum += g_optab[instr->code - 1].carry;
		else if (instr->arg_codes[i] == 1)
			sum += T_REG;
		else if (instr->arg_codes[i] == 3)
			sum += IND_SIZE;
		i++;
	}
	if (g_optab[instr->code - 1].codage)
		sum += 1;
	instr->bytes = sum;
	g_bytes += instr->bytes;
}

void					check_type(int arg_code, t_instr *instr, int index)
{
	int					size;

	if (arg_code == IND_CODE)
		size = T_IND;
	if (arg_code == DIR_CODE)
		size = T_DIR;
	if (arg_code == REG_CODE)
		size = T_REG;
	if ((size & g_optab[instr->code - 1].args[index]) != size)
		e2("This type of argument is forbidden here...",
		"stupid children were thrown off a cliff in Sparta. You're lucky!");
}

void					remove_cur_args(t_plr *plr)
{
	plr->ins_num++;
	if (plr->cur_args[0])
		ft_strdel(&plr->cur_args[0]);
	if (plr->cur_args[1])
		ft_strdel(&plr->cur_args[1]);
	if (plr->cur_args[2])
		ft_strdel(&plr->cur_args[2]);
}

int						process_instr(t_instr *instr, t_plr *plr)
{
	int					index;
	int					i;

	i = 0;
	instr->code = find_instruction_id(instr->command);
	index = instr->code - 1;
	if (check_arg_num(plr->args, g_optab[index].num_arg, plr))
	{
		while (i < g_optab[index].num_arg)
		{
			if (detect_type(plr->cur_args[i], instr, i))
			{
				check_type(instr->arg_codes[i], instr, i);
				i++;
			}
			else
				e2("Invalid argument...", "just like you");
		}
		count_bytes(instr);
	}
	else
		e2("Wrong args number...",
		"you skipped than counting lesson in school, didn't you");
	remove_cur_args(plr);
	return (0);
}
