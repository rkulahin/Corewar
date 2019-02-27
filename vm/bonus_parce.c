/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_parce.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 09:21:59 by rkulahin          #+#    #+#             */
/*   Updated: 2019/02/27 15:09:16 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		valid_log(t_vm *all, int ac, char **av, int i)
{
	int		index;

	if (i >= ac - 2)
		error("BAD_LOG_INDEX");
	index = ft_atoi(av[i + 1]);
	if (index <= 0 || index > 32 || !str_of_num(av[i + 1]))
		error("BAD_LOG_INDEX");
	if (all->nbr_log != 0)
		error("SECOND_LOG_INDEX");
	all->nbr_log = index;
	return (i + 2);
}
