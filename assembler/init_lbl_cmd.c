/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lbl_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakoven <yyakoven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 14:22:12 by vshreder          #+#    #+#             */
/*   Updated: 2019/03/25 19:10:20 by yyakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

t_instr					*create_instr(char *name)
{
	t_instr				*instr;

	instr = (t_instr *)malloc(sizeof(t_instr));
	*instr = (t_instr) {0, 0, 0, 0, {0, 0, 0}, {0, 0, 0}, 0, 0};
	instr->command = name;
	return (instr);
}

t_label					*create_label(char *str)
{
	t_label				*label;

	label = (t_label *)malloc(sizeof(t_label));
	*label = (t_label){str, 0, 0};
	return (label);
}

void					is_unique(t_label *label, t_label *head)
{
	while (head)
	{
		if (ft_strequ(head->name, label->name))
		{
			e2("A label with that name is clearly the extra one...",
			"like your last chromosome");
		}
		head = head->next;
	}
}

void					add_label(t_label *label, t_label **head)
{
	is_unique(label, *head);
	if (!*head)
	{
		*head = label;
	}
	else
	{
		label->next = *head;
		*head = label;
	}
}

void					add_instr(t_instr *instr, t_plr *plr)
{
	if (!plr->instr)
	{
		plr->instr = instr;
	}
	else
	{
		plr->last->next = instr;
	}
	plr->last = instr;
}
