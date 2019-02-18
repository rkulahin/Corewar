/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 18:21:46 by rkulahin          #+#    #+#             */
/*   Updated: 2019/02/18 19:19:56 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_carriage	*copy_carriage(t_carriage *cr)
{
	t_carriage	*new;

	new = (t_carriage *)malloc(t_carriage);
	new->carry = cr->carry;
	new->cycle = 0;
	new->live = 0;
	new->nbr_plr = cr->nbr_plr;
	new->regist = cr->regist;
	new->next = NULL;
}

void		op_fork(t_vm *vm, t_carriage *cr)
{
	t_carriage	*new;

	
	new = copy_carriage(cr);
}